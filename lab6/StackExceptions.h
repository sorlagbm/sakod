#pragma once
#include <exception>
#include <string>

class OverflowException : public std::exception {

private:

	std::string message;

public:

	OverflowException(const std::string& error = "") {
		message = error;
	}
	const char* what() const noexcept { return message.c_str(); }

};

class EmptyListException : public std::exception {

private:

	std::string message;

public:

	EmptyListException(const std::string& error = "") {
		message = error;
	}
	const char* what() const noexcept { return message.c_str(); }

};


