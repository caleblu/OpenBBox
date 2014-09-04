
#ifndef OBBNODE_H
#define OBBNODE_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <stdio.h>
#include <receivervideoudp.h>

//DECODER
//#include "QVideoDecoder.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QQueue>
#include "consoleserverpacket.h"
#include "receiverbehaviortcp.h"
#include "config.h"

typedef struct SubInfo_struct {
    bool status;
    QString name;
    u_int8_t id;

} SubInfo;

typedef struct BehaviorEvent_struct {
    uint pin;
    uint trials;
    uint pushes;
    uint rewards;
    long time;
    long time_u;

} BehaviorEvent;

class OBBNode : public QThread
{
    Q_OBJECT
private:
    char macStr[sizeof("00:00:00:00:00:00")];
    int                  idtask;
    QString              task;
    int                  iddatabase;
    u_int8_t             sizeCamerasPort;
    u_int8_t             mac[MAC_ADDRESS_SIZE];
    u_int16_t            portConsole;
    u_int16_t            portVideo[MAX_CAMERAS];
    u_int16_t            portBehavior;
    u_int16_t            portTask;
    u_int32_t            ipAddress;
    char                 label[MAX_LABEL_SIZE];
    SubInfo              subject;
    BehaviorEvent        lastEvent;

    QList<ReceiverVideoUDP*> receiverListCameras;
    ReceiverBehaviorTCP * receiverBehavior;
    QString generateFileName(int port);

public:
    OBBNode(u_int16_t * portVideo, u_int16_t portBehavior, u_int16_t portBTask, char * label, u_int8_t * mac, uint32_t ipAddress, u_int16_t portConsole);
    ReceiverVideoUDP * getVideoStream(int index);
    ReceiverBehaviorTCP * getBehaviorStream();

    char * getLabel();
    int getNumberOfVideoStream();
    int getPortController();

    void addNewReceiverVideo(u_int16_t port, int delayFrame);
    char * getMacAddress();
    u_int32_t getIPAdress();
    u_int16_t getBehaviorPort();
    u_int16_t getTaskPort();

    void setCurrentTask(int idtask);
    int getCurrentTask();

    void setIDDatabase(int id);
    int getIDDatabase();

    void setSubject(SubInfo sub);
    SubInfo getSubject();

    void setLastEvent(BehaviorEvent lastEvent);
    BehaviorEvent getLastevent();

    void setTask(QString task);
    QString getTask();

signals:
    //Signal to output frame to be displayed
    void processedImage(const QImage &image, QString info);
    void processedImageBuffer(uchar * buffer, uint size, QString info);

};

#endif // OBBNODE_H
