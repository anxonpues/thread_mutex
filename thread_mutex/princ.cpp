#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex carMutex;

void driveCar(string driverName) {
	unique_lock<mutex> carLock(carMutex);
	// the following 3 lines are critical job
	// need to stay locked when executed to prevent
	// simultaneous executing with mutex
	cout << driverName << " is driving " << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << driverName << " is done driving " << endl;
	// after the end of critical job  do unlock
	carLock.unlock();
}

int main()
{
	thread t1(driveCar, "Saldina");
	thread t2(driveCar, "Eithan");

	t1.join();
	t2.join();


	cin.get();
}