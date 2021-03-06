#include "socket_server.h"

struct mg_server* SocketServer::s_server = NULL;
// mutex SocketServer::queueMutex;
PiIO* SocketServer::pPiIO;

SocketServer::SocketServer()
{
}

SocketServer::~SocketServer()
{
}


void SocketServer::startup(PiIO* pi_io)
{
  pPiIO = pi_io;
  // gameShow = _gameshow;
  // printf("_gameshow pointer is %p\n", _gameshow);
  // printf("gameShow pointer is %p\n", gameShow);
  // printf("starting up server\n");startup
 SocketServer::runThread();
  // std::thread t1(SocketServer::runThread);
  // t1.detach();

  // std::thread t2(SocketServer::messagePusher);
  // t2.detach();
}

void SocketServer::runThread(){
  // printf("at run thread\n");
   // struct mg_server *server;

  // Create and configure the server
  s_server = mg_create_server(NULL, SocketServer::ev_handler);
  mg_set_option(s_server, "document_root", "./public_html");
  mg_set_option(s_server, "listening_port", "8080");

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(s_server, "listening_port"));
  for (;;) {
    mg_poll_server(s_server, 100);
    // usleep(1000);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&s_server);
}

void SocketServer::sendMessage(string message)
{
  // cout << "Trying to send " << message << endl;
  if(NULL != s_server){
    struct mg_connection *c;
    for (c = mg_next(s_server, NULL); c != NULL; c = mg_next(s_server, c)) {
      // struct conn_data *d2 = (struct conn_data *) c->connection_param;
      // printf("a\n");
      if (!c->is_websocket){
        continue;
      }
      // printf("b\n");
      // data.c_str(), data.length()
      mg_websocket_printf(c, WEBSOCKET_OPCODE_TEXT, "%s", message.c_str());
      // printf("c\n");
    }
  }
}


int SocketServer::ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:
      if(!strcmp(conn->uri, "/ws")){
        return sendWsReply(conn);
      }else{
        // printf("%s\n",conn->uri);
        return MG_FALSE;
      }
    default: return MG_FALSE;
  }
}

int SocketServer::sendWsReply(struct mg_connection *conn)
{
  if(conn->is_websocket){
    // cout << "WS: " << conn->content << endl;

    printf("%.*s\n", (int) conn->content_len, conn->content);
    if((int) conn->content_len >= 2047){
      cout << "======= WS message too big ========" << endl;
      printf("[%.*s]\n", (int) conn->content_len, conn->content);
      exit(0);
    }
    
    char buffer[2048];

    memcpy(buffer, conn->content, (int) conn->content_len);
    buffer[(int) conn->content_len] = 0;

    Document document;
    document.Parse(buffer);

    if(!document.IsObject()){
      cout << "-- malformed json message --" << endl;
      return MG_FALSE;
    }
    if(!document.HasMember("message")){
      cout << "-- json doesnt contain node 'message' --" << endl;
      return MG_FALSE; 
    }
    processMessage(&document);

    return MG_TRUE ;
  }else{
    return MG_FALSE;
  }
}

void SocketServer::processMessage(Document* document){
  string message = document->FindMember("message")->value.GetString();
  cout << "Got message " << message << endl;

  if(message.compare("shift_out") == 0){
    pPiIO->shiftOut(document);
  }else if(message.compare("get_pins") == 0){
    sendMessage(pPiIO->getInfoString());
  }else if(message.compare("set_direction") == 0){
    int pin_idx = document->FindMember("idx")->value.GetInt();
    string tmp = document->FindMember("direction")->value.GetString();
    if(tmp.compare("out") == 0){
      pPiIO->setPinMode(pin_idx, OUTPUT);
    }else{
      pPiIO->setPinMode(pin_idx, INPUT);
    }
  }else if(message.compare("set_state") == 0){
    int pin_idx = document->FindMember("idx")->value.GetInt();
    string tmp = document->FindMember("state")->value.GetString();
    if(tmp.compare("on") == 0){
      pPiIO->pinWrite(pin_idx, HIGH);
    }else{
      pPiIO->pinWrite(pin_idx, LOW);
    }
  }
}
