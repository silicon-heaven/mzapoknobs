#include "theapp.h"

#include "appclioptions.h"

#include <shv/iotqt/rpc/clientconnection.h>
#include <shv/coreqt/log.h>

#include <QTimer>

using namespace shv::chainpack;

TheApp::TheApp(int &argc, char **argv, AppCliOptions *cli_opts)
	: Super(argc, argv)
	, m_cliOptions(cli_opts)
{
	m_rpcConnection = new shv::iotqt::rpc::ClientConnection(this);

	if(!cli_opts->serverScheme_isset())
		cli_opts->setServerScheme("wss");
	if(!cli_opts->serverHost_isset())
		cli_opts->setServerHost("pisa-virt.felk.cvut.cz");
	if(!cli_opts->serverPort_isset())
		cli_opts->setServerPort(3778);
	if(!cli_opts->user_isset())
		cli_opts->setUser("guest");
	if(!cli_opts->password_isset())
		cli_opts->setPassword("guestpass");
	m_rpcConnection->setCliOptions(cli_opts);

	connect(m_rpcConnection, &shv::iotqt::rpc::ClientConnection::brokerConnectedChanged, this, &TheApp::onBrokerConnectedChanged);
	connect(m_rpcConnection, &shv::iotqt::rpc::ClientConnection::rpcMessageReceived, this, &TheApp::onRpcMessageReceived);

	QTimer::singleShot(0, m_rpcConnection, &shv::iotqt::rpc::ClientConnection::open);
}
/*
void TheApp::sendRpcMessage(const shv::chainpack::RpcMessage &msg)
{
	if(m_rpcConnection->isBrokerConnected()) {
		m_rpcConnection->sendMessage(msg);
	}
}
*/
void TheApp::onBrokerConnectedChanged(bool is_connected)
{
	shvInfo() << "shv broker connected:" << is_connected;
}

void TheApp::onRpcMessageReceived(const shv::chainpack::RpcMessage &msg)
{
	shvLogFuncFrame() << msg.toCpon();
	if(msg.isRequest()) {
		RpcRequest rq(msg);
		shvDebug() << "RPC request received:" << rq.toPrettyString();
	}
	else if(msg.isResponse()) {
		RpcResponse rp(msg);
		shvDebug() << "RPC response received:" << rp.toPrettyString();
	}
	else if(msg.isSignal()) {
		RpcSignal nt(msg);
		shvDebug() << "RPC notify received:" << nt.toPrettyString();
		/*
		if(nt.method() == Rpc::NTF_VAL_CHANGED) {
			if(nt.shvPath() == "/test/shv/lublicator2/status") {
				shvInfo() << lublicatorStatusToString(nt.params().toUInt());
			}
		}
		*/
	}
}
