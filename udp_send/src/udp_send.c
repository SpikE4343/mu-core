// udp_send

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "udp_send.h"
#include "wifi_controller.h"

#define MSG_COUNT (2)//((32000*sizeof(float)*3)/MAX_MESSAGE_DATA_SIZE)

static UdpSendConfig_t* config;
static int sockfd;
static QueueHandle_t sendQueue;
static QueueHandle_t freeQueue;
struct sockaddr_in servaddr;

static NetMessage_t messageList[MSG_COUNT];
 
void udpSendTask(void* arg)
{
    NetMessage_t* message=NULL;
    while (1) 
    {
        printf("UdpSend: waiting for message..\n");
        if( xQueueReceive(sendQueue, &message, portMAX_DELAY) == pdFALSE )
        {
            continue;
        }

        printf("Sending message: %u\n", message->dataLen);

        sendto(
            sockfd, 
            message->data, 
            message->dataLen, 
            0, 
            (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

        xQueueSend(freeQueue, &message, portMAX_DELAY);
    }
}

void udpSendInit(UdpSendConfig_t* cfg)
{
    printf("udpsend init\n");
    config = cfg;
     
    sendQueue = xQueueCreate(MSG_COUNT, sizeof(NetMessage_t*));
    freeQueue = xQueueCreate(MSG_COUNT, sizeof(NetMessage_t*));

    //memset(messageList, 0, sizeof(messageList));
    memset(&servaddr, 0, sizeof(servaddr));
    
    NetMessage_t* pmsg;
    for(int m=0; m<MSG_COUNT; ++m)
    {
        pmsg = &messageList[m];
        xQueueSend(freeQueue, &pmsg, portMAX_DELAY);
        printf("Queue size: %X, %X, %u, %u\n", (uint)freeQueue, (uint)&(messageList[m]), uxQueueSpacesAvailable(freeQueue), sizeof(NetMessage_t*));
    }



    xEventGroupWaitBits(wifiGetEventGroup(), BIT0, false, true, portMAX_DELAY);

    sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sockfd < 0) 
    {
        printf("Failed to create socket. Error %d", errno);
        return;
    }
     
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(config->port);
    servaddr.sin_addr.s_addr = ipaddr_addr(config->host);
     
    xTaskCreate(udpSendTask, "udp-send", 1024 * 2, NULL, 10, NULL);
}

void udpSend(NetMessage_t* msg)
{
    xQueueSend(sendQueue, &msg, portMAX_DELAY);
}

NetMessage_t* udpSendGetMessage()
{
    NetMessage_t* msg=NULL;
    xQueueReceive(freeQueue, &msg, 0);
    return msg;
}