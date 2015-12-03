#include "command.h"
#include <iostream>
#include <sys/wait.h>
#include <boost/xpressive/xpressive.hpp>

using namespace std;
using namespace boost::xpressive;

const sregex validation_token = *(alnum | '/' | '.' | '-' | '\\' | ' ' | '~' | '|');
const sregex parsing_token = +_s;

command::command()
: exit_requested_(false)
{
}
bool command::readline() {
	string command;
	cout << getlogin() << ", what would you like to do? ";
	getline(cin, command);
	this->history_.push_back(command);
	return parse_line(command);
}

void command::print_usage() const {
	cout << "Oh, here's how you can use me:" << endl;
	cout << "Available commands:  " << endl;
	cout << "help		Display this awesome information" << endl;
	cout << "exit		Exit this sweet interface (I'd hate to see you go)" << endl;
	cout << "history		Shows all the commands I can remember" << endl;
	cout << "history <x>	Executes the command from <x> position in my mind" << endl;
	cout << "		" << endl;
	cout << "cd		Change the current directory" << endl;
}

void command::execute() {
	vector<string>::iterator param_it = this->parameters_.begin();
	string cmd = *param_it;
	param_it++;

	if (cmd == "exit") this->exit_requested_ = true;
	else if (cmd == "help") print_usage();
	else if (cmd == "history" && param_it != this->parameters_.end()) {
		int position;
		istringstream ( this->parameters_[1] ) >> position;
		this->parameters_.clear();
		parse_line(this->history_[position]);
		execute();
	}
	else if (cmd == "history") {
		cout << "This is all I can remember. I'm sorry: " << endl;
		int i = 0;
		for (vector<string>::iterator hist_it = this->history_.begin() ; hist_it != this->history_.end(); ++hist_it){
    		cout << i << ": " << *hist_it << endl;
    		i++;
		}
	}
	else {
		// TODO: Execute the command.
		// Hint: check execvp
		pid_t  pid=0;

		if ((pid = fork()) == 0) {
			vector<char *> argv(parameters_.size() + 1);
			for (size_t i = 0; i != parameters_.size(); i++){
				argv[i] = &parameters_[i][0];
			}
			execvp(argv[0], argv.data());
			exit(0);
		}
		else {
			wait(NULL);
		}
	}
	this->parameters_.clear();
}

bool command::is_valid_command_line(const string& line) const {
	return regex_match( line, validation_token );
}

bool command::parse_line(const string& line) {
	// TODO: Parse command
	// Hint: check boost::expressive::sregex
	// 			   boost::expressive::sregex_iterator
	if (is_valid_command_line(line)){
		sregex_token_iterator cur( line.begin(), line.end(), parsing_token, -1 ), end;
		
		// Fix the heading space being left by the token_iterator from user input
		if(cur != end){
			this->parameters_.push_back(*cur);
			++cur;
			if (this->parameters_.front().compare(" ") < 0){
				this->parameters_.clear();
			}
		}

		for( ; cur != end; ++cur ) {
			this->parameters_.push_back(*cur);
		}
		cout << endl;
		return true;
	}

	return false;

}