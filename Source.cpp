#include "Header.h"

#define C "C:/"
#define D "D:/"

int main() { setlocale(LC_ALL, "ru");

int TimerData = 0;
std::thread ThrTime(Timer::Times, std::ref(TimerData));

 
	auto uniq = std::make_unique<Collect>();
	auto uniq2 = std::make_unique<Write>("Data.txt");
	auto uniq3 = std::make_unique<Check>();
	


	uniq->ShowDirectory(C);
	uniq3->CheckEx(MainPending);

	
	ThrTime.join();
}