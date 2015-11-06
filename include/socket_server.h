#ifndef _SOCKET_SERVER_H
#define _SOCKET_SERVER_H

#include "common_defines.h"
#include "pi_io.h"


using namespace std;

#include <thread>
#include <string.h>
#include <queue>
#include <mutex>

class SocketServer
{
public:
  SocketServer();
  ~SocketServer();
  static void startup(PiIO* pi_io);

  static void sendMessage(string message);
  // void startup();

  // static void enqueueMessage(string message);

  // static Document* getNextIncomingMessage();

  
private:

  static int ev_handler(struct mg_connection *conn, enum mg_event ev);
  static void runThread();

  static int sendWsReply(struct mg_connection *conn);
  // static string dequeueMessage();
  static void messagePusher();
  static void processMessage(Document* document);

  // std::thread socketThread;

  // static GameShow* gameShow;
  static struct mg_server *s_server;
  // static queue<string> messages;
  // static queue<Document*> incomingMessages;

  static mutex queueMutex;

  static PiIO *pPiIO;
  
};

#endif //_SOCKET_SERVER_H