#ifndef __ABC_CONFIGURATION_CONFIGURATION_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATION_HEADER__

#include <string>
#include <vector>

namespace abc {



class Configuration {

public:

	enum Type {
		Category,
		Text,
		Select,
		Trigger
	};

	Configuration(const char* name, Type type) : 
		name_(name), type_(type) { }

	inline std::string& name() { return name_; }
	inline Type type() { return type_; }
	inline std::string& text() { return text_; }
	inline std::vector<std::string>& items() { return items_; }

	inline void addChild(Configuration c) { children_.push_back(c); }

protected:

	Type type_;
	std::string name_;
	std::string text_;
	std::vector<std::string> items_;
	std::vector<Configuration> children_;

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATION_HEADER__

