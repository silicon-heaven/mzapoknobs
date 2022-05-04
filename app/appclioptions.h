#pragma once

#include <shv/iotqt/rpc/clientappclioptions.h>

class AppCliOptions : public shv::iotqt::rpc::ClientAppCliOptions
{
private:
	using Super = shv::iotqt::rpc::ClientAppCliOptions;
public:
	AppCliOptions();
/*
	CLIOPTION_GETTER_SETTER2(bool, "tester.enabled", is, set, TesterEnabled)
	CLIOPTION_GETTER_SETTER2(std::string, "tester.script", t, T, esterScript)

	CLIOPTION_GETTER_SETTER2(std::string, "sysfs.rootDir", s, setS, ysFsRootDir)
	CLIOPTION_GETTER_SETTER2(std::string, "app.connStatusFile", c, setC, onnStatusFile)
	CLIOPTION_GETTER_SETTER2(int, "app.connStatusUpdateInterval", c, setC, onnStatusUpdateInterval)
	*/
};

