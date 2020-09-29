# SocketTestProj
a primary proj to test socket coding in Linux

## 这个项目是用来练习Linux下socket编程的，以下为总结的经验：

### TCP客户端一般流程
- 新建套接字；
- 设置目标服务器的Port和IP Addr；
- 尝试连接服务器；
- 发送信息；
- 关闭套接字。

### TCP服务端一般流程
- 新建套接字；
- 设置套接字选项；
- 绑定自身的Port，和可以接受的IP Addr；
- 监听连接；
- 捕获连接；
- 接收套接字；
- 信息处理；
- 关闭套接字；
- 返回**捕获连接**这一步。

### 具体实现可看代码，Tcp客户端为client.c，Tcp服务端为Server.c
