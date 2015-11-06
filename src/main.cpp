#include "pi_io.h"
#include "socket_server.h"

int main(void){
  PiIO* pPiIO = new PiIO();
  pPiIO->startup();
  
  SocketServer* pSocketServer = new SocketServer();
  pSocketServer->startup(pPiIO);
}
