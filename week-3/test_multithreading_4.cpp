#include <iostream>
#include <mutex>
#include <thread>
#include <iomanip>
#include <ctime>
using namespace std;
using std::chrono::system_clock;

int main(){
	cout << "The id of current thread is " << this_thread::get_id << endl;

	//get current time

	time_t cur_time = system_clock::to_time_t(system_clock::now());

	//convert to time struct
	struct tm *time = localtime(&cur_time);
	cout << put_time(time, "%X") << endl;
	// cout << put_time(time, "%x") << endl;

	cout << "Waiting for the next minute to begin ......... \n";
	time->tm_min++;
	time->tm_sec = 0;

	//sleep until the next minute is not reached
	this_thread::sleep_until(system_clock::from_time_t(mktime(time)));
	cout << put_time(time, "%X") << " reached!\n";

	//sleep for 5s
	this_thread::sleep_for(chrono::seconds(5));
	
	time_t end_time = system_clock::to_time_t(system_clock::now());
	time = localtime(&end_time);
	cout << put_time(time, "%X") << endl;
	cout << "Running Time: " << end_time - cur_time << endl; 
}
