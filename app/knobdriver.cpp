#include "knobdriver.h"
#include "theapp.h"

#include <shv/chainpack/rpcmessage.h>
#include <shv/iotqt/rpc/clientconnection.h>

#include <QFrame>
#include <QSlider>
#include <QSpinBox>

using namespace shv::chainpack;

KnobDriver::KnobDriver(QFrame *parent, const QString &shv_path)
	: QObject{parent}
	, m_knobFrame(parent)
	, m_shvPath(shv_path)
{
	auto *slider = parent->findChild<QSlider*>("slider");
	Q_ASSERT(slider);
	auto *spinbox = parent->findChild<QSpinBox*>("spinbox");
	Q_ASSERT(spinbox);
	connect(slider, &QSlider::valueChanged, this, [=](int val) {
		spinbox->setValue(val);
		auto *conn = TheApp::instance()->rpcConnection();
		RpcRequest rq;
		rq.setRequestId(conn->nextRequestId());
		rq.setShvPath(m_shvPath.toStdString());
		rq.setMethod(Rpc::METH_SET);
		rq.setParams(slider->value());
		conn->sendMessage(rq);
	});
}
