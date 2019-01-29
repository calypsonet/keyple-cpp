#pragma once

#include <iostream>
#include <stdexcept>

class Logger {
private:
	bool traceEnabled;
	bool debugEnabled;

	void log(const char *s)
	{
		while (s && *s) {
			if (*s=='%' && *++s!='%')	// make sure that there wasn't meant to be more arguments
							// %% represents plain % in a format string
				 throw std::runtime_error("invalid format: missing arguments");
			std::cout << *s++;
		}
	}

public:
	Logger() {
		traceEnabled = 0;
		debugEnabled = 0;
	}

	bool isTraceEnabled() {
		return traceEnabled;
	}

	bool isDebugEnabled() {
		return debugEnabled;
	}

	void trace(const char* s)
	{
		log(s);
	}

	template<typename T, typename... Args>
	void trace(const char* s, T value, Args... args) {
		while (s && *s) {
			if (*s=='%' && *++s!='%') {	// a format specifier (ignore which one it is)
				std::cout << value;		// use first non-format argument
				return trace(++s, args...); 	// ``peel off'' first argument
			}
			std::cout << *s++;
		}
		throw std::runtime_error("extra arguments provided to printf");
	}

	void debug(const char* s)
	{
		log(s);
	}

	template<typename T, typename... Args>
	void debug(const char* s, T value, Args... args) {
		while (s && *s) {
			if (*s=='%' && *++s!='%') {	// a format specifier (ignore which one it is)
				std::cout << value;		// use first non-format argument
				return debug(++s, args...); 	// ``peel off'' first argument
			}
			std::cout << *s++;
		}
		throw std::runtime_error("extra arguments provided to printf");
	}

	void warn(const char* s)
	{
		log(s);
	}

	template<typename T, typename... Args>
	void warn(const char *s, T value, Args... args) {
		while (s && *s) {
			if (*s=='%' && *++s!='%') {	// a format specifier (ignore which one it is)
				std::cout << value;		// use first non-format argument
				return warn(++s, args...); 	// ``peel off'' first argument
			}
			std::cout << *s++;
		}
		throw std::runtime_error("extra arguments provided to printf");
	}
};