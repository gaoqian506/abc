#ifndef __ABC_CONFIGURATION_CONFIGURATION_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATION_HEADER__

#include <string>
#include <vector>
#include <memory>	// shared_ptr

using namespace std;

namespace abc {

class Configurable;

class Configuration {

public:

	enum Type { Unknown = 0, Category, Text, Select, Trigger, Display };

	Configuration(Configurable* owner, const string& name, Type type) : 
		owner_(owner), name_(name), type_(type) { }

	inline Configurable* owner() { return owner_; }
	inline string& name() { return name_; }
	inline Type& type() { return type_; }
	inline string& text() { return text_; }
	inline vector<string>& items() { return items_; }

	shared_ptr<Configuration> child(const string& name);
	inline void addChild(shared_ptr<Configuration>& c) { children_.push_back(c); }

private:

	Configurable* owner_;
	Type type_;
	string name_;
	string text_;
	vector<string> items_;
	vector<shared_ptr<Configuration>> children_;

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATION_HEADER__

