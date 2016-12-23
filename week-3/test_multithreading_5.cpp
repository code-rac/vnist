#include <iostream>
#include <mutex>
#include <thread>
#include <iomanip>
#include <ctime>
#include <vector>
#include <windows.h>
using namespace std;
using std::chrono::system_clock;
std::mutex m;
vector <int> vec;
void _push(){
	m.lock();
	for(int i = 0; i < 10; i++){
		cout << "Push " << i << endl;
		Sleep(500);
		vec.push_back(i);
	}
	m.unlock();
}

void _pop(){
	m.lock();
	for(int i = 0; i < 10; i++){
		if(vec.size() > 0){
			int val = vec.back();
			vec.pop_back();
			cout << "Pop " << val << endl;
		}
		Sleep(500);
	}
	m.unlock();
}


int main(){
	thread tpush(_push);
	thread tpop(_pop);
	if(tpush.joinable())
		tpush.join();
	if(tpop.joinable())
		tpop.join();
	cout << vec.size() << endl;

}
