#include "theapp.h"
#include "mainwindow.h"
#include "appclioptions.h"

#include <shv/chainpack/rpcmessage.h>
#include <shv/coreqt/utils.h>
#include <shv/coreqt/log.h>

#include <necrolog.h>

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
	// call something from shv::coreqt to avoid linker error:
	// error while loading shared libraries: libshvcoreqt.so.1: cannot open shared object file: No such file or directory
	shv::coreqt::Utils::qVariantToRpcValue(QVariant());

	QCoreApplication::setOrganizationName("CTU");
	QCoreApplication::setApplicationName("mzapoknobs");
	QCoreApplication::setApplicationVersion("0.0.1");

#ifdef Q_OS_WASM
	NecroLog::setColorizedOutputMode(NecroLog::ColorizedOutputMode::No);
	NecroLog::setTopicsLogTresholds("rpcmsg");
#endif

	std::vector<std::string> shv_args = NecroLog::setCLIOptions(argc, argv);

	//NecroLog::registerTopic("Tester", "Tester");
	//NecroLog::registerTopic("RunCmd", "Run shell commands, scripts");

	AppCliOptions cli_opts;
	cli_opts.parse(shv_args);
	if(cli_opts.isParseError()) {
		for(const std::string &err : cli_opts.parseErrors())
			shvError() << err;
		return EXIT_FAILURE;
	}
	if(cli_opts.isAppBreak()) {
		if(cli_opts.isHelp()) {
			cli_opts.printHelp(std::cout);
		}
		return EXIT_SUCCESS;
	}
	for(const std::string &s : cli_opts.unusedArguments()) {
		shvWarning() << "Undefined argument:" << s;
	}

	if(!cli_opts.loadConfigFile()) {
		return EXIT_FAILURE;
	}

	shv::chainpack::RpcMessage::registerMetaTypes();

	TheApp a(argc, argv, &cli_opts);
	MainWindow w;
	w.show();
	return a.exec();
}
