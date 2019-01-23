//#include "includes.h"

#include "chatserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>

#include <QProcess>

QT_USE_NAMESPACE

//! [constructor]
ChatServer::ChatServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR)
  , m_process(Q_NULLPTR)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Listening port:" << port ;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &ChatServer::onNewConnection);
    }

//    openApp("C:/Program Files (x86)/eDx/Video Streamer 2017.1/",
//            "C:/Program Files (x86)/eDx/Video Streamer 2017.1/Video Stream Tool.exe",
//            QStringList("C:/Program Files (x86)/eDx/Video Streamer 2017.1/Video Stream Tool.exe")
//            );
}

ChatServer::~ChatServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}
//! [constructor]

//! [onNewConnection]
void ChatServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "new webSocket client:" << pSocket->peerAddress() << pSocket->requestUrl() << pSocket->resourceName() << pSocket->origin() << pSocket->localAddress() << pSocket->localPort();
     QStringList urlSplits = pSocket->resourceName().split("/");
     QString clientName = "";
     if (urlSplits.size() > 0){
        clientName = urlSplits.value(urlSplits.size() - 1);
     }

    connect(pSocket, &QWebSocket::textMessageReceived, this, &ChatServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &ChatServer::socketDisconnected);

    m_clients << pSocket;
    m_clientNames[clientName] = pSocket;
}
//! [onNewConnection]

//! [processMessage]
void ChatServer::processMessage(QString message)
{
    QString to = "";
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(message.toUtf8(), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            if(obj.contains("to"))
            {
                QJsonValue name_value = obj.take("to");
                if(name_value.isString())
                {
                    to = name_value.toString();
                }
            }
        }
    }else
    {
        qDebug() <<"WebSocket client send data error:" << json_error.errorString();
    }

    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    if (to == "all")
    {
        //qDebug() << "all: " << m_clients.count();
        for (QWebSocket *pClient : qAsConst(m_clients)) {
            if (pClient != pSender) //don't echo message back to sender
            {
                pClient->sendTextMessage(message);
            }
        }
    } else if (m_clientNames.contains(to))
    {
        //qDebug() << "just send to: " << to;
        QWebSocket *pTo = m_clientNames.value(to);
        pTo->sendTextMessage(message);
        pTo = NULL;
    }
}
//! [processMessage]

//! [socketDisconnected]
void ChatServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        //qDebug() << "Disconnected: " << m_clientNames.key(pClient);
        m_clients.removeAll(pClient);
        m_clientNames.remove(m_clientNames.key(pClient));
        pClient->deleteLater();

    }
}

void ChatServer::openApp(QString workDirector, QString path, QStringList param)
{
    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(workDirector);
    myProcess->start(path, param);
    myProcess->waitForStarted(1000);
    //qDebug() << myProcess->state();
}
//! [socketDisconnected]
