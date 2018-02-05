#ifndef __ABC_CONFIGURATION_CONFIGURABLE_HEADER__
#define __ABC_CONFIGURATION_CONFIGURABLE_HEADER__


#include <string>	// std::string
#include <memory>	// std::shared_ptr
#include <glog/logging.h>



namespace abc {

class Configuration;
class Configurable {

public:

	/** @brief constructor. */
	Configurable();
	/** @brief destructor. */
	virtual ~Configurable();

	/** @brief query method of name. */
	inline const std::string& name() const { return name_; }

	/** @brief query method of configuration. */
	inline Configuration* configuration() const { return configuration_; }

	/** @brief will be called by configurator. */
	virtual void config(Configuration* configuration, const std::string& param) { 
		// TODO implement this func when add some configurtions;
		LOG(INFO) << "Should implement this func when add some configurtions.";
	}




protected:
	Configuration* configuration_;
	inline void add_configuration_for_auto_release(Configuration* configuration) {
		configuration_auto_release.push_back(configuration);
	}
	inline void set_name(const std::string& name) { name_ = name; }

private:
	std::string name_;
	std::vector<Configuration*> configuration_auto_release;


};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURABLE_HEADER__

