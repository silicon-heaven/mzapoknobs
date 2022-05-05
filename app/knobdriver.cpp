#include "knobdriver.h"
#include "theapp.h"

#include <shv/chainpack/rpcmessage.h>
#include <shv/iotqt/rpc/clientconnection.h>
#include <shv/coreqt/log.h>

#include <QFrame>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>

using namespace shv::chainpack;

KnobDriver::KnobDriver(QFrame *parent, const QString &shv_path)
	: QObject{parent}
	, m_knobFrame(parent)
	, m_shvPath(shv_path)
{
	auto *slider = parent->findChild<QSlider*>({});
	Q_ASSERT(slider);
	auto *spinbox = parent->findChild<QSpinBox*>({});
	Q_ASSERT(spinbox);
	spinbox->setMaximum(100);
	slider->setMaximum(spinbox->maximum());
	auto *conn = TheApp::instance()->rpcConnection();
	connect(slider, &QSlider::valueChanged, this, [=](int val) {
		spinbox->setValue(val);
		RpcRequest rq;
		rq.setRequestId(conn->nextRequestId());
		rq.setShvPath(m_shvPath.toStdString());
		rq.setMethod(Rpc::METH_SET);
		rq.setParams(slider->value());
		conn->sendMessage(rq);
	});
	QTimer *refresh_timer = new QTimer(this);
	connect(refresh_timer, &QTimer::timeout, this, [=]() {
		RpcRequest rq;
		m_refreshDataRequestId = conn->nextRequestId();
		rq.setRequestId(m_refreshDataRequestId);
		rq.setShvPath(m_shvPath.toStdString());
		rq.setMethod(Rpc::METH_GET);
		rq.setParams(slider->value());
		shvInfo() << m_knobFrame->objectName() << "sending refresh request:" << rq.toCpon();
		conn->sendMessage(rq);
	});
	connect(conn, &shv::iotqt::rpc::ClientConnection::rpcMessageReceived, this, [=](const RpcMessage &msg) {
		if(msg.isResponse()) {
			RpcResponse resp(msg);
			if(resp.requestId().toInt() == m_refreshDataRequestId) {
				shvInfo() << m_knobFrame->objectName() << "refresh response received:" << resp.toCpon();
				if(resp.isSuccess())
					slider->setValue(resp.result().toInt());
			}
		}
	});
	refresh_timer->start(2000);
}
