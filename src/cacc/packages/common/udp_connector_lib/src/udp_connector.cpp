#include <udp_connector_lib/udp_connector.h>

namespace Udp_ns{
UdpConnector::UdpConnector(int _port){
    port = _port;

    tv.tv_sec = 0;
    tv.tv_usec = 10000; 
    
    init();
};   

UdpConnector::~UdpConnector(){
    close(socket_var);
};

void UdpConnector::init(){
    //Setting for UDP
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_port = htons(port);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    socket_var = socket(AF_INET, SOCK_DGRAM, 0);
    if(setsockopt(socket_var, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval))) perror("Error in setsockopt()");
};

UdpSender::UdpSender(std::string _destination, unsigned short _port):UdpConnector(_port){
    destination = _destination;
    
    init();
};
    
void UdpSender::init(){
    //Setting for UDP
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_addr.s_addr = inet_addr(destination.c_str());
    sock_addr.sin_port = htons(port);
    sock_addr.sin_family = AF_INET;
    
    socket_var = socket(AF_INET, SOCK_DGRAM, 0);
    if(setsockopt(socket_var, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval))) perror("Error in setsockopt()");
};

UdpSender::~UdpSender(){
    close(socket_var);
};

UdpReceiver::UdpReceiver(unsigned short _port):UdpConnector(_port){    
    init();

    bind(socket_var, (const struct sockaddr *) &sock_addr, sizeof(sock_addr));
};
    
UdpReceiver::~UdpReceiver(){
    close(socket_var);
};

};
