QT       += core gui

QT += core gui widgets network websockets

CONFIG += c++17

TEMPLATE = app
TARGET = mzapoknobs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = $$SHV_PROJECT_TOP_BUILDDIR/bin

LIBDIR = $$DESTDIR
unix: LIBDIR = $$SHV_PROJECT_TOP_BUILDDIR/lib

wasm {
	message ( WASM build )
	LIBS += \
		$$LIBDIR/libnecrolog.a \
		$$LIBDIR/libshvchainpack.a \
		$$LIBDIR/libshvcore.a \
		$$LIBDIR/libshvcoreqt.a \
		$$LIBDIR/libshviotqt.a \
}
else {
	LIBS += \
			-L$$LIBDIR \

	LIBS += \
		-lnecrolog \
		-lshvchainpack \
		-lshvcore \
		-lshvcoreqt \
		-lshviotqt \

	unix {
			LIBS += \
					-Wl,-rpath,\'\$\$ORIGIN/../lib\'
	}
}

INCLUDEPATH += \
	../3rdparty/necrolog/include \
	../3rdparty/libshv/libshvchainpack/include \
	../3rdparty/libshv/libshvcore/include \
	../3rdparty/libshv/libshvcoreqt/include \
	../3rdparty/libshv/libshviotqt/include \

SUBDIRS += \
	3rdparty \

SOURCES += \
	knobdriver.cpp \
    main.cpp \
	mainwindow.cpp \
	appclioptions.cpp \
	theapp.cpp

HEADERS += \
	knobdriver.h \
mainwindow.h \
appclioptions.h \
	theapp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
