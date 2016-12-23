#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

void threadFunc(){
	cout << "Welcome to Multithreading" << endl;
}
void printSomeValues(int val, char *str, double dval){
	cout << val << " " << str << " " << dval << endl;
}
class myFunctorParam{
public:
	void operator()(int *arr, int length){
		cout << "An array of length " << length << " is passed to thread " << endl;
		for(int i = 0; i < length; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	void changeSign(int *arr, int length){
		cout << "An array of length " << length << " is pass to thread: " << endl;
		for(int i = 0; i < length; i++)
			cout << arr[i] << "  ";
		cout << endl;
		cout << "Changing sign of all elements of initial array:" << endl;
		for(int i = 0; i < length; i++){
			arr[i] *= -1;
			cout << arr[i] << "  ";
		}
	}

};



int main(){
	//create 3 different threads
	thread t1(threadFunc);
	thread t2(threadFunc);
	thread t3(threadFunc);

	//get id of all the threads
	auto id1 = t1.get_id();
	auto id2 = t2.get_id();
	thread::id id3 = t3.get_id();

	//join all the threads
	if(t1.joinable()){
		t1.join();
		cout << "Thread with id " << id1 << " is terminated." << endl; 
	}
	if(t2.joinable()){
		t2.join();
		cout << "Thread with id " << id2 << " is terminated." << endl; 
	}

	if(t3.joinable()){
		t3.join();
		cout << "Thread with id " << id3 << " is terminated." << endl; 
	}

}
