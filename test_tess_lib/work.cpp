#include "work.h"

worker::worker(QObject *parent) : QThread(parent)
{
	tid = 0;
}


void worker::run()
{ 
	tid = GetCurrentThreadId();
	listenEvent();//  
}


