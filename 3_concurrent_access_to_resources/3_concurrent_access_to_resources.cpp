/********* 3_concurrent_access_to_resources *********/
// 3.1 competition
// 3.2 mutex

#include <unistd.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
vector<int> vec;
mutex m;

void push() {
    // m.lock();
    unique_lock<mutex> n(m);
    for (size_t i = 0; i < 10; ++i) {
        cout << "Push " << i << endl;
        usleep(500);
        vec.push_back(i);
    }
    // m.unlock();
    n.unlock();
}

void pop() {
    // m.lock();
    unique_lock<mutex> n(m);
    for (int i = 0; i != 10; ++i) {
        if (vec.size() > 0) {
            int val = vec.back();
            vec.pop_back();
            cout << "Pop " << val << endl;
        }
        usleep(500);
    }
    // m.unlock();
    n.unlock();
}

void makeACall() {
    m.lock();  // person enters the call box and locks the door
    // now it can talk to his friend without any interruption
    cout << " Hello my friend, this is " << this_thread::get_id() << endl;
    // this person finished to talk to his friend
    m.unlock();  // and he leaves the call box and unlock the door
}

int main() {
// example 1
#if true
    thread in(push);
    thread out(pop);
    if (in.joinable()) in.join();
    if (out.joinable()) out.join();
    for (auto val : vec) {
        cout << val << endl;
    }
#endif

// exmaple 2  In fact this exmaple can not tell the theory well because lock or unlock the id must to be different
#if false
    thread person1(makeACall);
    thread person2(makeACall);
    thread person3(makeACall);
    if (person1.joinable()) person1.join();
    if (person2.joinable()) person2.join();
    if (person3.joinable()) person3.join();
#endif
    return 0;
}
