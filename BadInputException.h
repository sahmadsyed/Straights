#ifndef BADINPUTEXCEPTION_H
#define BADINPUTEXCEPTION_H

#include <string>

class BadInputException{
public:
	explicit BadInputException(std::string);
	~BadInputException(){}
	std::string getMessage() const;
private:
	std::string err_message;
};

#endif
