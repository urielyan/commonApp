/*-------------------------------------------------------------------------------
文件名称： chartserver.h
文件描述： 定义一个webSocket 服务端。
备    注：
        交互服务器作用：
        为了各程序之间的数据，操作交互。所有客户端均通过url 访问服务器，发送给其他客户端的数据需要指定 目的地 name。
        与服务器交互方式：
        服务器程序装在一台电脑上之后，所有客户端通过IP+地址访问，默认端口为1234。
        若本地程序访问可使用ws://127.0.0.1:1234/name=your Name

        公用协议：
            "name": "当前客户端对象名和url中最后name 保持一致",
        特殊key
        name: 当前客户端名
        All:	其他所有客户端。
        To: 目的地客户端

        特殊协议：
        中控发送数据给仪表
        "name": "CenterControlMap"
        , "to": "meter1"
        , "isCenterControl":"yes"
        , "rotationType":rotationType
        , "description": route.getStep(currentStep).getDescription(false)
        "nextStepDistance": 0

        , "isMessage": "yes"
        , "message": "墨玉南路行驶810米，左转进入安礼路"

        在QML 中的一个定义例子：
    WebSocket {
        id: webSocket
        url: "ws://127.0.0.1:1234/meter1"
        onTextMessageReceived: {
            console.log(message)
            var jsonData = JSON.parse(message)
            if (jsonData.hasOwnProperty("isCenterControl") && jsonData.isCenterControl === "yes")
            {
                if (jsonData.hasOwnProperty("description"))
                {
                    currentDesciption.text = jsonData.description
                }
                if (jsonData.hasOwnProperty("nextStepDistance"))
                {
                    nextStepDistance.text = jsonData.nextStepDistance
                }
                if (jsonData.hasOwnProperty("rotationType"))
                {
                    var rotationType = jsonData.rotationType;
                    if (rotationType === 1 || rotationType === 0)
                    {
                        hudMap.source = "qrc:/meter/dynamicStyleRES/image/direct.png"
                    }else if (rotationType === 7)
                    {
                        hudMap.source = "qrc:/meter/dynamicStyleRES/image/left.png"
                    }else if (rotationType === 3)
                    {
                        hudMap.source = "qrc:/meter/dynamicStyleRES/image/right.png"
                    }
                }
            }

            if (jsonData.hasOwnProperty("isMessage") &&  jsonData.isMessage === "yes" && jsonData.hasOwnProperty("message"))
            {
                messageText.text = jsonData.message
                messageTextAnimation.restart()
            }
        }

        在HTML 中的 一个例子：

            {
               // 打开一个 web socket
               ws = new WebSocket("ws://192.168.1.131:1234/CenterControlMap");

               ws.onopen = function()
               {
                  // Web Socket 已连接上，使用 send() 方法发送数据
                  ws.send('{"self-introduce":"我是CenterControlMap"}');
                  //alert("数据发送中...");
               };

               ws.onmessage = function (evt)
               {
                  var received_msg = evt.data;
                  //document.getElementById("demo").innerHTML = received_msg;

                  var messageJsonObject = JSON.parse(received_msg);
                  if (messageJsonObject.isMessage == "yes")
                  {
                    alert(messageJsonObject.message);
                  }
               };
            }
                    var sendText = {
                        "name": "CenterControlMap"
                        , "to": "meter1"
                        , "isCenterControl":"yes"
                        , "rotationType":rotationType
                        , "description": route.getStep(currentStep).getDescription(false)
                        , "nextStepDistance":  map.getDistance(paths[i], route.getStep(currentStep ).getPosition())

                        , "isMessage": "yes"
                        , "message": "墨玉南路行驶810米，左转进入安礼路"
                    }


                //		, "isMessage": "yes"
                    //	, "message": "墨玉南路行驶810米，左转进入安礼路"
                    //alert(route.getStep(currentStep).getDescription())

                    //var o = JSON.parse(sendText);
                    //document.getElementById("demo").innerHTML=JSON.stringify(sendText)
                    //ws.send(route.getStep(currentStep).getDescription() + route.getStep(currentStep).getPosition().lng + route.getStep(currentStep).getPosition().lat);
                    if (ws.readyState===1)
                    {
                        ws.send(JSON.stringify(sendText))
                    }


作者   ：闫葛
完成日期：2019.1.11
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/
#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QMap>
#include <QString>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QProcess)

class ChatServer : public QObject
{
    Q_OBJECT
public:
    explicit ChatServer(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~ChatServer();

private Q_SLOTS:
    void onNewConnection();

    /**
     * @brief   处理webSocket客户端发送过来的消息
     * @param[in]   message 客户端发送的消息，必须是json文档
     * @return
     * @note
     */
    void processMessage(QString message);
    void socketDisconnected();
    void openApp(QString workDirector, QString path, QStringList param);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QMap<QString, QWebSocket *> m_clientNames;
    QProcess *m_process;
};

#endif //CHATSERVER_H
