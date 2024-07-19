#ifndef WEBSERVER_H
#define WEBSERVER_H
// 避免重复定义。这种技术被称为头文件的防御式声明（Header Guard）或者头文件的包含保护。

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>
#include <string>

#include "../threadpool/threadpool.h"
#include "../http/http_conn.h"
#include "../config/config.h"

const int MAX_FD = 65535;               // 最大的文件描述符数量（用于控制epoll的数量）
const int MAX_EVENT_NUMBER = 10000;     // 最大的事件数量（事件作为任务放入到任务队列中）
const int TIME_SLOT = 5;                // 等待时间，单位秒，当连接在Timeslot的时间内重新发送，就会重置时间（用于HTTP请求）

// 服务器类，main函数创建一个服务器类进行执行
// 服务器类为主要建立连接的类，用于建立和客户端的连接线程池、数据库的连接池等等
class Server {
public:
    // Server的无参构造函数
    Server();

    // Server的析构函数
    ~Server();

    // 初始化服务器命令行信息
    bool server_init(Config config);

    // 初始化服务器数据库信息
    bool server_init(string username, string password, string databasename);

private:
    // ------ 服务器信息 ------
    int m_port;                 // 服务器运行的端口号
    int m_actor_mode;           // 核反应堆模式
    
    // ------ 数据库信息 ------
    string m_username;          // 数据库的用户名
    string m_password;          // 数据库的密码
    string m_database_name;     // 要连接的数据库的名字

    // ------ 网络通信信息 ------
    int m_lfd;                  // Server需要监听客户端发来的请求，lfd为监听的文件描述符
    int m_lfd_trig_mode;        // 监听文件描述符的trig模式
    int m_cfd_trig_mode;        // 通信文件描述符的trig模式
    int m_socket_linger_opt;    // socket是否开启linger模式
    
    // ------ 日志信息 -------

};

#endif