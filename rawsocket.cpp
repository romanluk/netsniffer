#include "rawsocket.h"

RawSocket::RawSocket() {
    WSADATA info;
    WSAStartup(MAKEWORD(2, 2), &info);
    SOCKADDR_IN socket_address;
    char hostname[128];

    socket_ = socket(AF_INET, SOCK_RAW, IPPROTO_IP);

    gethostname(hostname, sizeof(hostname));
    HOSTENT *host_info = gethostbyname(hostname);

    ZeroMemory(&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = ((struct in_addr *)host_info->h_addr_list[0])->s_addr;
    bind(socket_, (SOCKADDR *)&socket_address, sizeof(SOCKADDR));
}

IpHeader* RawSocket::Sniff() {
    IpHeader *header = nullptr;
    char buffer[MAX_PACKET_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int size = recv(socket_, buffer, sizeof(buffer), 0);

    if (size >= sizeof(IpHeader)) {
        header = new IpHeader();
        memcpy(header, buffer, sizeof(buffer));
    }

    return header;
}