#ifndef KNOBDRIVER_H
#define KNOBDRIVER_H

#include <QObject>

class QFrame;

class KnobDriver : public QObject
{
	Q_OBJECT
public:
	explicit KnobDriver(QFrame *parent, const QString &shv_path);

private:
	QFrame *m_knobFrame;
	QString m_shvPath;
	int m_refreshDataRequestId = 0;
};

#endif // KNOBDRIVER_H
