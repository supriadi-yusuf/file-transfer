#include <iostream>
#include <string>
#include <sstream>

#include "tcpfileserver.h" 

using namespace std;

void tcp_file_sender( const int& argc, const char* const * const& argv){

  if( argc != 3){    
    cout << "Should be " << argv[0] << " <port> <file_name>" << endl;
    throw 1;
  }

  int tcp_port;
  stringstream ss_port;

  ss_port << argv[1];  
  ss_port >> tcp_port;

  TcpFileServer server( tcp_port, argv[2]);
  
  server.run(); 
}

int main(int argc, char* argv[])
{ 
  try {
     tcp_file_sender(argc, argv); 
  }catch( ... ){
     cout << "Error happened ... " << endl;
  }
  return 1;
}

