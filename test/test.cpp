
#include "abc/configuration/configuration.h"
#include "abc/asynchronous/runner.h"
#include "abc/configuration/configurator.h"
#include "abc/configuration/consoleconfigurator.h"
#include "abc/program/program.h"
#include "abc/deeplearning/dlprogram.h"
#include "abc/imageprocessing/imageprocessing.h"

#include "abc/example/mark.h"


#include <glog/logging.h>


	//enum Type { Category = 0, Text, Trigger, Status };

	/** @brief constructor with owner, type and text. */
	//Configuration(Configurable* owner, Type type, 
	//	const std::string& text = "") : 
	//	owner_(owner), type_(type), text_(text) {}

	/** @brief query attribute of owner. */
	//inline const Configurable* owner() { return owner_; }

	/** @brief query attribute of type. */
	//inline const Type& type() { return type_; }

	/** @brief query attribute of text. */
	//inline const std::string& text() { return text_; }


	/** @brief query attribute of description. */
	//inline const std::string& description() { return description_; }

	/** @brief query or set attribute of child with name. */
	//inline std::shared_ptr<Configuration>& operator[](const std::string& name) 
	//{ return  children_[name]; }


int main(int argc, char** argv) {

	google::InitGoogleLogging(argv[0]);
	FLAGS_alsologtostderr = 1;
	//FLAGS_log_dir = "./";

	{

		abc::Configuration config(0, abc::Configuration::Category);
		LOG(INFO) << "Configuration initialization passed.";

		CHECK(config.owner() == 0) << "Configuration get owner failed.";

		abc::Configuration* pconfig1 = new abc::Configuration(0, abc::Configuration::Text, "test1");
		abc::Configuration* pconfig2 = new abc::Configuration(0, abc::Configuration::Action, "test2");
		abc::Configuration* pconfig3 = new abc::Configuration(0, abc::Configuration::Status, "test3");

		CHECK(pconfig1->name() == "test1") << "Configuration name check failed.";
		CHECK(pconfig2->name() == "test2") << "Configuration name check failed.";
		CHECK(pconfig3->name() == "test3") << "Configuration name check failed.";

		config.add_child(pconfig1);
		config.add_child(pconfig2);
		config.add_child(pconfig3);
		LOG(INFO) << "Configuration add child passed.";

		CHECK(config.type() == abc::Configuration::Category) << "Configuration type check failed.";

		CHECK(config.child("test1") == pconfig1) << "Configuration get child failed.";
		CHECK(config.child("test2") == pconfig2) << "Configuration get child failed.";
		CHECK(config.child("test3") == pconfig3) << "Configuration get child failed.";
		CHECK(config.child("test4") == 0) << "Configuration get child failed.";

		LOG(INFO) << "Configuration element query passed.";

		CHECK(config.owner() == 0) << "Configuration owner checking failed.";

		CHECK(config.type() == abc::Configuration::Category) << "Configuration type check failed.";
		CHECK(pconfig1->type() == abc::Configuration::Text) << "Configuration type check failed.";
		CHECK(pconfig2->type() == abc::Configuration::Action) << "Configuration type check failed.";
		CHECK(pconfig3->type() == abc::Configuration::Status) << "Configuration type check failed.";

		LOG(INFO) << "Configuration testing passed.";		


		delete pconfig1;
		delete pconfig2;
		delete pconfig3;
		LOG(INFO) << "Configuration destroy passed.";

	}

	{
		abc::Configurable* configurable = new abc::Configurable();
		LOG(INFO) << "Configurable initialization passed.";
		CHECK(configurable->name() == "Configurable") << "Configurable default name check failed.";


		CHECK(configurable->configuration()) << "Configurable get configuration check failed.";
		

		delete configurable;
		LOG(INFO) << "Configuration destroy passed.";
	}

	{

		abc::Runner* runner = new abc::Runner();
		LOG(INFO) << "Runner initialization passed.";
		CHECK(runner->name() == "Runner") << "Runner default name check failed.";
		CHECK(runner->running() == false) << "Runner default state check failed.";

		runner->run();
		runner->run();
		runner->run();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		CHECK(runner->running() == true) << "Runner's running state check failed.";

		runner->stop();
		CHECK(runner->running() == false) << "Runner's stoped state check failed.";	

		//runner = new abc::Runner();
		runner->run();
		//runner->join();
		delete runner;

		LOG(INFO) << "Runner testing passed.";

	}

	{
		LOG(INFO) << "Begin testing Configurator.";

		abc::Configurator* configurator = 
			abc::Configurator::factory(abc::Configurator::None);
		CHECK(configurator == 0) << "Configurator's factory creator check failed.";

		LOG(INFO) << "Configurator testing passed.";	

	}

	{


		LOG(INFO) << "---------------------\
		Testing Runner\
		-------------------------";		

		class TestRunner : public abc::Runner {
		private:
			virtual bool beforeRuning() { return false; }

		};

		TestRunner runner;

		LOG(INFO) << "(Testing...) Runner run first time.--------------------";	
		runner.run();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		LOG(INFO) << "(Testing...) Runner run second time.--------------------";	
		runner.run();
		LOG(INFO) << "(Testing...) Runner passed.";	
		//return 0;
	}	


	{

		LOG(INFO) << "---------------------\
		Testing String's find\
		-------------------------";				
		std::string str;
		str = "abcdefg";
		str.erase(0);
		LOG(INFO) << "After abcdefg.erase(0):" << str;

		str = "abcdefg";
		str.erase(3);
		LOG(INFO) << "After abcdefg.erase(3):" << str;


		str = "abcdefg";
		str.erase(std::string::npos+1);
		LOG(INFO) << "After abcdefg.erase(npos+1):" << str;	


		str = "abcdefg";
		str.erase(str.find_last_not_of(" \t"));
		LOG(INFO) << "After abcdefg.erase(find_last_not_of(' ')+1):" << str;

		str = "abcdefg";
		LOG(INFO) << "npos = " << std::string::npos << std::endl;
		LOG(INFO) << "find_last_not_of(' ')+1) = " << str.find_last_not_of(" \t") << std::endl;	
	}


	{

		LOG(INFO) << "---------------------\
		Testing ConsoleConfigurator\
		-------------------------";		
		abc::Configurator* configurator = 
			abc::Configurator::factory(abc::Configurator::Console);
		CHECK(configurator) << "Console's factory creator check failed.";

		delete configurator;
		LOG(INFO) << "Console destroy passed.";	

		configurator = abc::Configurator::factory(abc::Configurator::Console);
		abc::ConsoleConfigurator* console = 
			static_cast<abc::ConsoleConfigurator*>(configurator);
		CHECK(console) << "Console static cast from Configruator failed.";

		LOG(INFO) << "Please interac with console configurator.\n";
		//console->run();
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("hello");
		LOG(INFO) << "ConsoleConfigurator invalid command passed.";
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("help");
		LOG(INFO) << "ConsoleConfigurator help command passed.";
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("status");
		LOG(INFO) << "ConsoleConfigurator status command passed.";
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("exit");
		LOG(INFO) << "ConsoleConfigurator exit command passed.";
		std::cout << "Press enter to continue...\n";
		console->join();
		LOG(INFO) << "ConsoleConfigurator join passed.";

		LOG(INFO) << "Please interac with console configurator again.\n";
		//console->run();
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("hello");
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("help");
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("status");
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		console->exec("exit");	
		std::cout << "Press enter to continue...\n";
		//console->join();
		delete console;

		LOG(INFO) << "Console testing passed.";	

	}

	{

		LOG(INFO) << "---------------------\
		Testing Program\
		-------------------------";

		abc::Program* program = new abc::Program();
		LOG(INFO) << "Program instantiation succeed";

		//program->start();
		LOG(INFO) << "Starting program succeed";


		delete program;
		LOG(INFO) << "Destroy program succeed";		

	}


	{

		LOG(INFO) << "---------------------\
		Testing TestProgram\
		-------------------------";		

		class TestProgram : public abc::Program {
		private:
			virtual bool after_started() {
				abc::Configurator* configurator = 
					configurators_[abc::Configurator::Console];
				CHECK(configurator) << "Default program configurator check failed.";
				abc::ConsoleConfigurator* console = 
					static_cast<abc::ConsoleConfigurator*>(configurator);
				CHECK(console) << "Console static cast from Configruator failed.";

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("hello");
				LOG(INFO) << "ConsoleConfigurator invalid command passed.";
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "ConsoleConfigurator help command passed.";
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("status");
				LOG(INFO) << "ConsoleConfigurator status command passed.";
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("program.run");
				console->exec("help");
				console->exec("status");
				LOG(INFO) << "Program run from console scceed.";
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("program.stop");
				console->exec("help");
				console->exec("status");				
				LOG(INFO) << "Program stop from console scceed.";
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));				
				console->exec("program.run");
				console->exec("help");
				console->exec("status");
				LOG(INFO) << "Program run again from console scceed.";

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("exit");	
				std::cout << "Press enter to continue...\n";
				console->join();
				LOG(INFO) << "ConsoleConfigurator join passed.";

				return false;
			}

		};

		TestProgram test_program;
		test_program.start();
		LOG(INFO) << "TestProgram start passed.";
	}



	{


		LOG(INFO) << "---------------------\
		Testing Deep Learning Program\
		-------------------------";		

		class TestDlProgram : public abc::DlProgram {
		public:
			TestDlProgram() {
			}
		private:


			virtual bool after_started() {

				LOG(INFO) << "DlProgram's configuration count:" << 
					configuration_->children_count();

				abc::Configurator* configurator = 
					configurators_[abc::Configurator::Console];
				CHECK(configurator) << "Default program configurator check failed.";
				abc::ConsoleConfigurator* console = 
					static_cast<abc::ConsoleConfigurator*>(configurator);
				CHECK(console) << "Console static cast from Configruator failed.";

				
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram configurations check passed.";

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.train");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.train");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram train check passed.";		

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.test");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram test check passed.";

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.test");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram test check passed.";	

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.stop");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram stop check passed.";

				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.stop");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram stop check passed.";	


				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.switch");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram switch check passed.";	
								
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.gpu_id 2");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram gpu_id check passed.";


				network_ = (abc::DeepNetwork*)5;
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.train");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram train check passed.";						


				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.test");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram test check passed.";	



				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.stop train");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram stop train passed.";	



				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("dlprogram.stop test");
				//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "(Testing...) DlProgram stop test passed.";	
				network_ = 0;

				return false;
/*
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("hello");
				LOG(INFO) << "ConsoleConfigurator invalid command passed.";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("help");
				LOG(INFO) << "ConsoleConfigurator help command passed.";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("status");
				LOG(INFO) << "ConsoleConfigurator status command passed.";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("program.run");
				console->exec("help");
				console->exec("status");
				LOG(INFO) << "Program run from console scceed.";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("program.stop");
				console->exec("help");
				console->exec("status");				
				LOG(INFO) << "Program stop from console scceed.";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));				
				console->exec("program.run");
				console->exec("help");
				console->exec("status");
				LOG(INFO) << "Program run again from console scceed.";

				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				console->exec("exit");	
				std::cout << "Press enter to continue...\n";
				console->join();
				LOG(INFO) << "ConsoleConfigurator join passed.";
*/				
			}

		};


		TestDlProgram test_dl_program;
		test_dl_program.start();
		LOG(INFO) << "Test Deep Learning Program start passed.";		
	}


	{


		LOG(INFO) << "---------------------" <<
		"Testing Image Processing" <<
		"-------------------------";	

		std::vector<std::string> back_names = abc::ImageProcessing::find("example/data/mark/background");
		CHECK(back_names.size() > 0) << "[Imageprocessing] Check find failed.";

		std::vector<std::string> mark_names = abc::ImageProcessing::find("example/data/mark/mark");
		CHECK(mark_names.size() > 0) << "[Imageprocessing] Check find failed.";

		LOG(INFO) << "[Imageprocessing] Find testing passed.";

		
		cv::Mat back_image = abc::ImageProcessing::random_read(back_names);
		CHECK(!back_image.empty()) << "[Imageprocessing] Check random_read failed.";

		int name_id = 0;
		cv::Mat mark_image = abc::ImageProcessing::random_read(mark_names, &name_id);
		CHECK(!mark_image.empty()) << "[Imageprocessing] Check random_read failed.";
		CHECK(name_id >= 0 && name_id < mark_names.size()) << 
			"[Imageprocessing] Check random_read out index failed.";
		//int class_id = abc::ImageProcessing::parse_num(mark_names[name_id], 0, '_');

		cv::Mat mask = abc::ImageProcessing::overlap(back_image, mark_image);
		CHECK(!mark_image.empty()) << "[Imageprocessing] Check overlap failed.";
		abc::ImageProcessing::save("test/output/overlap1.jpg", back_image);
		abc::ImageProcessing::save("test/output/mask1.jpg", mask);
		LOG(INFO) << "[ImagProcessing] overlap test passed";

		back_image = abc::ImageProcessing::random_read(back_names);
		mask = cv::Mat(back_image.size(), CV_8U, cv::Scalar(0));
		for (int i = 0; i < 10; i++) {
			cv::Mat mark_image = abc::ImageProcessing::random_read(mark_names, &name_id);
			CHECK(!mark_image.empty()) << "[Imageprocessing] Check random_read failed.";
			CHECK(name_id >= 0 && name_id < mark_names.size()) << 
				"[Imageprocessing] Check random_read out index failed.";
			cv::Mat local_mask = abc::ImageProcessing::overlap(back_image, mark_image);
			CHECK(!mark_image.empty()) << "[Imageprocessing] Check overlap failed.";
			mask.setTo(255, local_mask);
		}

		abc::ImageProcessing::save("test/output/overlap2.jpg", back_image);
		abc::ImageProcessing::save("test/output/mask2.jpg", mask);
		LOG(INFO) << "[ImagProcessing] overlap test passed";
		LOG(INFO) << "[ImagProcessing] save test passed";


		CHECK(abc::ImageProcessing::parse_num("example/data/mark/background/dsf12_234-567.789.jpg",0) == 234) << "ImageProcessing parse_num check failed.";
		CHECK(abc::ImageProcessing::parse_num("example/data/mark/background/dsf12_234-567.789.jpg",4) == -1) << "ImageProcessing parse_num check failed.";
		int a1 = abc::ImageProcessing::parse_num("example/data/mark/background/dsf12_234-567.789.jpg",0);
		int a2 = abc::ImageProcessing::parse_num("example/data/mark/background/dsf12_234-567.789.jpg",2);
		int a3 = abc::ImageProcessing::parse_num("example/data/mark/background/dsf12_234-567.789.jpg",3);
		int a4 = abc::ImageProcessing::parse_num("aaa/bbb/000/111/ccc/abc123.456.789.jpg",0);

		CHECK(a1 == 234) << "ImageProcessing parse_num check failed.";
		CHECK(a2 == 789) << "ImageProcessing parse_num check failed.";
		CHECK(a3 == -1) << "ImageProcessing parse_num check failed.";
		CHECK(a4 == 456) << "ImageProcessing parse_num check failed.";
		LOG(INFO) << "example/data/mark/background/dsf12_234-567.789.jpg";
		LOG(INFO) << "ImageProcessing::parse_num out:"<<"\n"<<a1<<"\n"<<a2<<"\n"<<a3;

	}


	{

		LOG(INFO) << "---------------------" <<
		"Testing Mark Example" <<
		"-------------------------";		

		class TestMark : public example::Mark {

		public:
			TestMark(const int& argc, const char** argv) : 
				example::Mark(argc, argv) {}

		private:

			virtual bool after_started() {

				// abc::ConsoleConfigurator cc;
				// cc.add_configuration(configuration_);
				// cc.parse_file("example/data/mark/mark.config");

				LOG(INFO) << "[Mark] Background images.-----------------------";
				for (std::vector<std::string>::iterator itr = back_names_.begin();
					itr != back_names_.end(); ++itr) {
					LOG(INFO) << *itr;
				}
				LOG(INFO) << "[Mark] Background images.-----------------------";

				LOG(INFO) << "[Mark] mark images.-----------------------";
				for (std::vector<std::string>::iterator itr = mark_names_.begin();
					itr != mark_names_.end(); ++itr) {
					LOG(INFO) << *itr;
				}
				LOG(INFO) << "[Mark] mark images.-----------------------";



				LOG(INFO) << "[Mark] test images.-----------------------";
				for (std::vector<std::string>::iterator itr = test_names_.begin();
					itr != test_names_.end(); ++itr) {
					LOG(INFO) << *itr;
				}
				LOG(INFO) << "[Mark] test images.-----------------------";
		


				abc::ConsoleConfigurator* console = 
					static_cast<abc::ConsoleConfigurator*>
						(configurators_[abc::Configurator::Console]);
				CHECK(console) << "[TestMark] default configurator check passed";


				console->exec("mark.test");
				LOG(INFO) << "[TestMark] Console's mark.test command test passed.";


				console->exec("mark.train");
				LOG(INFO) << "[TestMark] Console's mark.test command test passed.";	



				console->exec("help");
				LOG(INFO) << "[TestMark]'s Console help command test passed.";

				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				return false;
			}
		};

		const char* args[2] = { "test/test", "example/data/mark/mark.config" };
		TestMark test_mark(2, args);
		test_mark.start();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LOG(INFO) << "[TestMark] Testing passed.";


	}



/*
	LOG(INFO) << "Begin testing configurator.";
	abc::Configuration* configuration_test1 =
		new abc::Configuration(configurable, abc::Configuration::Category);
	abc::Configurator* configurator_test1 =
		abc::Configurator::factory(abc::Configurator::None, configuration_test1);
	CHECK(configurator_test1 == 0) << "Configurator's factory check failed.";
	delete configuration_test1;

	LOG(INFO) << "Configurator testing passed.";


	LOG(INFO) << "Begin testing Console.";

	abc::Configuration* configuration_test2 =
		new abc::Configuration(configurable, abc::Configuration::Category);

	abc::Configurator* console_test1 = 
		abc::Configurator::factory(abc::Configurator::Console, configuration_test2);
	CHECK(console_test1) << "Console's factory creator check failed.";

	LOG(INFO) << "Console testing passed.";	

*/

	google::ShutdownGoogleLogging();

	//while(true); 

}
