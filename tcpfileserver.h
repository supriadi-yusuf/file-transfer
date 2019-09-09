#ifndef __tcpfileserver_h__
#define __tcpfileserver_h__

class TcpFileServer{
  private:
    int portno;
    const char* fileName;
    void sendFile(int client_socket);

  public:
    TcpFileServer(const int tcp_port, const char* const strfileName);
    void run();
};

#endif
