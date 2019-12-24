//

#ifndef __udp_send_h__INCLUDED__
#define __udp_send_h__INCLUDED__

#include <stdint.h>

#define MAX_MESSAGE_DATA_SIZE 1450

typedef struct 
{
    uint8_t data[MAX_MESSAGE_DATA_SIZE];
    uint16_t dataLen;
} NetMessage_t;

typedef struct
{
    char* host;
    uint16_t port;    
} UdpSendConfig_t;

void udpSendInit();
void udpSend(NetMessage_t*msg);
NetMessage_t* udpSendGetMessage(); 

#endif