#include "abc/example/mark.h"



int main(int argc, char** argv) {


	google::InitGoogleLogging(argv[0]);
	FLAGS_log_dir = "test/output";

	example::Mark mark(argc > 1 ? argv[1] : 0);
	return mark.start();

	//abc::Program* program = new abc::Program();
	//program->start();
	//delete program;

	//abc::DlProgram program2;
	//MarkDetectionProgram program2(argc, argv);
	//return program2.start();
	//return 0;


	//MarkDetectionProgram program(argc, argv);
	//return program.start();
	//return 0;

}

/*

http://serveo.net/
https://alternativeto.net/software/ngrok/

sudo vi /etc/init/ngrok.conf 
# Ngrok
#
# Create tunnel provided by ngrok.io

description "Ngrok Tunnel"

start on runlevel [2345]
stop on runlevel [!2345]

respawn
respawn limit 10 5
umask 022

exec /home/gq/Documents/tools/ngrok-official/ngrok tcp -config=/home/gq/.ngrok2/ngrok.yml 22
./ngrok -config=ngrok.cfg -proto=tcp 22


layers {  
  name: "prob"  
  type: “Softmax"  
bottom: " ip2"  
  top: "prob"  
}  

*/
