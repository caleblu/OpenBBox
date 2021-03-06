#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QThread>
#include <QQueue>
#include <QSemaphore>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "../OpenBBoxManager/streampacket.h"

const int sizeBehaviorPacket[] = {SIZE_CONTROL_HEADER + sizeof(BehaviorEventContext)/sizeof(u_int8_t),
                                  SIZE_CONTROL_HEADER + sizeof(BehaviorEventShow)/sizeof(u_int8_t)};

class TCPSender : public QThread
{
    Q_OBJECT
private:
    bool stop;
    bool test;
    QString ip;
    u_int16_t port;

    QQueue<BehaviorEventPacket> behaviorPackets;
    QSemaphore qsem;
    QSemaphore qsem_test;

public:
    explicit TCPSender(QString ip, u_int16_t port);
    void startSender(bool test);
    void stopSender();
    QSemaphore * getQsemaphore();

protected:
    void run();

signals:

public slots:
   void sendBehaviorPacket(BehaviorEventPacket packet);
   void sendBehaviorPackettest(BehaviorEventPacket packet);
};

#endif // TCPSENDER_H
