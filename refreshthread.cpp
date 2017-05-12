#include "refreshthread.h"

refreshThread::refreshThread()
{

}

void refreshThread::run()
{
    while(true)
    {
        msleep(1000);
        //emit SignalRefresh();
    }
}
