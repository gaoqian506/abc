#ifndef __ABC_CONFIGURATION_CONFIGURATION_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATION_HEADER__

#include <iostream> // std::cout
#include <string>	// std::string
//#include <map>		// std::map
#include <vector>	// std::vector
#include <memory>	// std::shared_ptr
#include <assert.h>	// assert


#include "configurable.h"


namespace abc {

class Configurable;
class Configuration {

public:

	/** @brief configuration type enumaration. */
	enum Type { Category = 0, Text, Action, Status };

	/** @brief constructor with owner, type and text. */
	Configuration(Configurable* owner = 0,
		const Type& type = Category,
		const std::string& name = "",
		const std::string& text = "",
		const std::string& description = "") : 
		owner_(owner), type_(type), name_(name),
		text_(text), description_(description), mute_(false) {}

	/** @brief query attribute of owner. */
	inline Configurable* owner() const { return owner_; }

	/** @brief query attribute of type. */
	inline const Type& type() const { return type_; }


	/** @brief query attribute of name. */
	inline std::string& name() { return name_; }	
	inline const std::string& name() const { return name_; }		

	/** @brief query attribute of text. */
	inline std::string& text() { return text_; }
	inline const std::string& text() const { return text_; }

	/** @brief query attribute of mute. */
	inline bool& mute() { return mute_; }
	inline const bool& mute() const { return mute_; }	


	/** @brief query attribute of description. */
	inline const std::string& description() const { return description_; }

	inline Configuration* child(const std::string& name) {
		for (std::vector<Configuration*>::iterator itr = children_.begin();
			itr != children_.end(); ++itr) {
			if ((*itr)->name() == name && !(*itr)->mute()) { return (*itr); }
		}
		return 0;
	}

	inline void add_child(Configuration* child) {
		if (child) {
			children_.push_back(child); 
		}
		else {
			std::cout << "Can not add zero poitor configuration child.\n";
		}

	}

	inline const std::vector<Configuration*>& children() const { return children_; }

	inline const int children_count() const { return children_.size(); }


private:
	Configurable* owner_;
	Type type_;
	std::string name_;
	std::string text_;
	std::string description_;
	bool mute_;
	std::vector<Configuration*> children_;

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATION_HEADER__

