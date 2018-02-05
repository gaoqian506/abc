#include "abc/configuration/configurable.h"
#include "abc/configuration/configuration.h"


namespace abc {

Configurable::Configurable() {
	LOG(INFO) << name() << " (Configurable)before constrct.";
	name_ = "Configurable";
	configuration_ = new Configuration(this, Configuration::Category, "root");
	add_configuration_for_auto_release(configuration_);
	LOG(INFO) << name() << " (Configurable)fater constrct.";

}

Configurable::~Configurable() {

	LOG(INFO) << name() << " (Configurable)before destroy, deleting configuration:" << \
		configuration_auto_release.size();

	for (std::vector<Configuration*>::iterator itr =
		configuration_auto_release.begin();
		itr != configuration_auto_release.end(); ++itr) {
		delete (*itr);
	}

	//LOG(INFO) << name() << " Destroied.";

	LOG(INFO) << name() << " (Configurable)after destroy.";	
}


} // namespace abc