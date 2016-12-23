#include <iostream>
#include <mutex>
#include <thread>
#include <iomanip>
#include <ctime>
#include <vector>
#include <windows.h>
#include <future>
using namespace std;
using std::chrono::system_clock;

int square(int x){
	return x*x;
}

int main(){
	auto a = (&square, 10);
	int v = a.get();
	cout << v << endl;
}
