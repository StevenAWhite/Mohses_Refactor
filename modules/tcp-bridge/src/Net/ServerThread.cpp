#include "ServerThread.h"

#ifdef WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#endif
using namespace std;

std::mutex ServerThread::mutex;

ServerThread::ServerThread() = default;

int ServerThread::Create(void* Callback, void* args) {
   int tret = 0;

   tid = std::thread((void* (*)(void*)) Callback, args);

   if (tret != 0) {
      cerr << "Error while creating threads." << endl;
      return tret;
   }

   // cout << "Thread successfully created." << endl;
   return 0;
}

int ServerThread::Join() {

   if (tid.joinable()) {
      tid.join();
      return 0;
   }
   return -1;
}

int ServerThread::InitMutex() {
   return 0;
}

/*
    LockMutex():
                Blocks until mutex becomes available
*/
int ServerThread::LockMutex(const string& identifier) {
   if (mutex.try_lock()) {
      return 0;
   }

   cerr << "Error while " << identifier << " was trying to acquire the lock"
      << endl;
   return -1;
}

int ServerThread::UnlockMutex(const string& identifier) {
   mutex.unlock();
   return 0;
}
