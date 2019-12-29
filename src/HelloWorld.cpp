/********* Basic Thread Info *********/
// 1. create a function thread
// 2. pass params into a thread
// 3. create a class thread
// 4. thread id

#include <iostream>
#include <thread>
using namespace std;

void hello() { cout << "Hello World" << endl; }

void printSomeValues(int val, char* str, double dval) { cout << val << " " << str << " " << dval << endl; }

class myFunctor {
   public:
    void operator()() { cout << "This is my function object" << endl; }
    void publicFunction() { cout << "public functon of myFunctor class is called" << endl; }
    void operator()(int* arr, int length) {
        cout << "An array of length " << length << " is passed to thread" << endl;
        for (int i = 0; i != length; ++i) cout << arr[i] << " " << endl;
        cout << endl;
    }
    void changeSign(int* arr, int length) {
        cout << "An arrray of length " << length << " is passed to thread" << endl;
        for (int i = 0; i != length; ++i) cout << arr[i] << endl;
        cout << "Changing sign of all elements of initial array" << endl;
        for (int i = 0; i != length; ++i) {
            arr[i] *= -1;
            cout << arr[i] << " ";
        }
    }
};

int main() {
// 1. create a function thread
#if false
    thread t(hello);
    t.detach();
    if (t.joinable()) {
        t.join();
    } else {
        cout << "thread t has been detached" << endl;
    }
#endif

// 2. pass params into a thread
#if false
    char* str = "hello";
    thread paramPass(printSomeValues, 5, str, 3.2);
    if (paramPass.joinable()) paramPass.join();
#endif

// 3. create a class thread
#if false
    myFunctor myFunc;
    // create a thread for a class
    thread functorTest(myFunc);
    if (functorTest.joinable()) functorTest.join();
    // create a thread for a public function of a class
    thread pfunctorTest(&myFunctor::publicFunction, myFunc);
    if (pfunctorTest.joinable()) pfunctorTest.join();
    // create a thread for a class with params
    int arr[5] = {1, 3, 5, 7, 9};
    thread paramToClass(myFunc, arr, 5);
    if (paramToClass.joinable()) paramToClass.join();
    // create a thread for a public function with params of a class
    thread paramToClassPublicFunc(&myFunctor::changeSign, &myFunc, arr, 5);
    if (paramToClassPublicFunc.joinable()) paramToClassPublicFunc.join();

#endif

// 4. thread id
#if false
    thread t1(hello);
    thread t2(hello);
    thread t3(hello);
    cout << "t1_thread_id = " << t1.get_id() << ", t2_thread_id = " << t2.get_id() << ", t3_thread_id = " << t3.get_id()
         << endl;
    t1.join();
    t2.join();
    t3.join();
#endif
    return 0;
}
