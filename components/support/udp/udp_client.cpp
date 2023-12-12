/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : udp_client.cpp
 * @brief     : 通讯接口的udp网络使用
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-10-07       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

/**on MCU*/
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include <lwip/sockets.h>

#include "udp/udp_client.hpp"

#if USE_OS

Udp::Udp()
{
    sockfd_ = -1;
}

void Udp::udp_open(uint32_t port)
{
    if (sockfd_ != -1)
    {
        udp_close();
    }
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ == -1)
    {
        printf("create socket error\n");
        configASSERT(0);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd_, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("bind error\n");
        configASSERT(0);
    }
}


void Udp::udp_close()
{
    if (sockfd_ != -1)
    {
        closesocket(this->sockfd_);
        sockfd_ = -1;
    }
}


int Udp::udp_send(const char *data, size_t len, const char *ip , uint16_t port)
{
    if (sockfd_ == -1)
    {
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    return sendto(sockfd_, data, len, 0, (struct sockaddr *)&addr, sizeof(addr));
}


int Udp::udp_recv(char *data, size_t len)
{
    if (sockfd_ == -1)
    {
        return -1;
    }
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    return recvfrom(sockfd_, data, len, 0, (struct sockaddr *)&addr, &addr_len);
}

#endif /* USE_OS */