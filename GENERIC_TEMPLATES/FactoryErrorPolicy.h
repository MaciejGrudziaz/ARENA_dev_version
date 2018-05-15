#pragma once
#include <fstream>

template<class AbstractProduct>
struct IgnoreError {
	AbstractProduct* NoCallback() { return nullptr; }
};

template<class AbstractProduct>
struct ExceptionError {
	void NoCallback() { throw std::runtime_error("Nieznany obiekt!"); }
};

template<class AbstractProduct>
struct QuitError {
	void NoCallback() { exit(0); }
};

template<class AbstractProduct>
struct LogFileError {
	std::string _filename;
	void SetLogFile(std::string _name) { _filename = _name; }
	void NoCallback() {
		std::fstream file(_filename, std::ios::out | std::ios::app);
		file << "Error! No callback function in Object Factory!";
		file.close();
		exit(0);
	}
};