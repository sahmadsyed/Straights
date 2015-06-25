#include <string>
#include "BadInputException.h"

using namespace std;

BadInputException::BadInputException(string msg){
	err_message = msg;
}

string BadInputException::getMessage() const{
	return err_message;
}

