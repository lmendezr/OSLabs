#include <iostream>
#include "command.h"
int main(){
	command cmd;
	do{
		if (!cmd.readline()){
			cmd.print_usage();
		}
		else{
			cmd.execute();
		}
	} while (!cmd.exit_requested());
	return 0;
}