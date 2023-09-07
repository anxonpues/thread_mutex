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
	int delay{ 5 };
	if (driverName == "Saldina")
		delay = 3;
	else		
		delay = 3*delay;
	cout << "--> delay --> " << delay << endl;
	this_thread::sleep_for(chrono::seconds(delay));
	cout << driverName << " is done driving " << endl;
	// after the end of critical job  do unlock
	carLock.unlock();
}

void driveCar2(string driverName) {
	lock_guard<mutex> carLock(carMutex);
	// the following 3 lines are critical job
	// need to stay locked when executed to prevent
	// simultaneous executing with mutex
	cout << driverName << " is driving " << endl;
	int delay{ 5 };
	if (driverName == "Saldina 2")
		delay = 3;
	else
		delay = 3 * delay;
	cout << "--> delay --> " << delay << endl;
	this_thread::sleep_for(chrono::seconds(delay));
	cout << driverName << " is done driving " << endl;
	// after the end of critical job  do not need to unlock
	// after lock_guard, because does it itself under block
	// leaving where lock_guard was used
	
}

int main()
{
	thread t1(driveCar, "Saldina");
	thread t2(driveCar, "Eithan");

	t1.join();
	t2.join();

	thread t3(driveCar2, "Saldina 2");
	thread t4(driveCar2, "Eithan 2");

	t3.join();
	t4.join();


	cin.get();
}