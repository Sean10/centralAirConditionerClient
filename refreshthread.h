#ifndef REFRESHTHREAD_H
#define REFRESHTHREAD_H

#include <QThread>

class refreshThread : public QThread
{
public:
    refreshThread();

protected:
    void run();

signals:
    void SignalRefresh();
};

#endif // REFRESHTHREAD_H
