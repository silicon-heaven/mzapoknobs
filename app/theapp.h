#pragma once

#include <QApplication>

class AppCliOptions;

namespace shv { namespace iotqt { namespace rpc { class ClientConnection; }}}
namespace shv { namespace chainpack { class RpcMessage; }}

class TheApp : public QApplication
{
	Q_OBJECT
	using Super = QApplication;
public:
	TheApp(int &argc, char **argv, AppCliOptions* cli_opts);

	static TheApp* instance() {return qobject_cast<TheApp*>(Super::instance());}
	AppCliOptions* cliOptions() {return m_cliOptions;}

	shv::iotqt::rpc::ClientConnection *rpcConnection() { return m_rpcConnection; }
	//void sendRpcMessage(const shv::chainpack::RpcMessage &msg);
private:
	void onBrokerConnectedChanged(bool is_connected);
	void onRpcMessageReceived(const shv::chainpack::RpcMessage &msg);
private:
	shv::iotqt::rpc::ClientConnection *m_rpcConnection = nullptr;
	AppCliOptions* m_cliOptions;
};

