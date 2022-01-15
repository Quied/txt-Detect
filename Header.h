#pragma once
#include <deque>
#include <functional>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
#include <Windows.h>
#include "Advance.h"
#include <thread>
#include <string>
#include <mutex>

#define LOG = "log.txt"
#define LOGS = "logs.txt"
#define README = "README.txt"

std::deque<boost::filesystem::path>	MainPending;
std::deque<boost::filesystem::path>	Pending;
std::list<boost::filesystem::path> FileTxt; 
std::vector<boost::filesystem::path> Verified;

bool WhileSecondTread = true;

class Collect {
public:


	std::function<void(std::string)> ShowDirectory = [&](std::string Path)  {
		std::cout << "--> Current Directory: " << Path  << std::endl << std::endl;
		for(const auto el : boost::filesystem::directory_iterator(Path)){
			std::cout << el.path() << std::endl;			
			MainPending.push_back(el);
		}
	};

	

	std::function<void(std::string)> SetPending = [&](std::string Path) {
		for(const auto el : boost::filesystem::directory_iterator(Path)){
			Pending.push_back(el);
		}
	};

	std::function<void()> CheckPendingData = [&]() {
		std::cout << "Amount of path: " << MainPending.size();
		std::cout << "1) Continue - " << std::endl;
		std::cout << "2) Remove - " << std::endl;
		std::cout << "3) Next - " << std::endl;
		int DATA; std::cout << "* "; std::cin >> DATA;

		if (Pending.size() == 0) return;

		switch (DATA) {
		case SELECT::CONTINUE: break;
		case SELECT::REMOVE:	MainPending.clear(); Pending.clear(); break;
		case SELECT::NEXT:
		default:  break;
		}
	};

};

struct Check {

	void CheckEx(std::deque<boost::filesystem::path> &D) {
		std::string DataEx;
		for (const auto el : D) {
			DataEx = boost::filesystem::extension(el);
			if (DataEx == ".txt") FileTxt.push_back(boost::filesystem::path(el));
		}
	}
};

class Timer {
public:

	static void Times(static int &Time) {
		while (WhileSecondTread) {
			Sleep(10);
			Time++;
			if (Time == Condition::MINUTE) { std::cout << "Minute" << std::endl; Time = 0; }
		}
	}

};

class Write {
public:

	std::ifstream Read_File;
	std::ofstream Write_File;
	std::string Path;
	std::vector<std::string> ReadData;

	Write(const std::string Pathh) : Write_File(Pathh), Path(Pathh) {
		if (Write_File.is_open()) {
			std::cout << Pathh << ": Is Open  |  " ;
			Write_File.close();
			std::cout << "Closed..." << std::endl;
		}
		else { std::cout << "File ERROR" << std::endl; }
	}

	std::function<void()> ReadFile = [&]() {
		Read_File.open(Path);
		std::string CopyDATA;
		while (Read_File.eof()) {
			std::getline(Read_File, CopyDATA);
			ReadData.push_back(CopyDATA);
			FileTxt.push_front(Path);
		}
		std::cout << "Read Lines" << ReadData.size();
		AddDataToFile();
		Read_File.close();
	};

	
	inline void AddDataToFile() {
		Write_File.open(this->Path, std::ofstream::app);

		for (const auto& el : ReadData) { Write_File << el; }
		ReadData.clear();

		Write_File.close();
	}

};