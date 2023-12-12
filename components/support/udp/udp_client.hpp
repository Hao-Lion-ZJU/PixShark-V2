
#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include "common.hpp"

#if USE_OS

class Udp
{
public:
    Udp();
    ~Udp() = default;

    void udp_open(uint32_t port);

    void udp_close();

    int udp_send(const char *data, size_t len, const char *ip = "192.168.1.11", uint16_t port = 5000);

    int udp_recv(char *data, size_t len);

private:
	int sockfd_;
};


#endif /* USE_OS */

#endif /* _UDP_CLIENT_H_ */

