#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define ETH_TYPE 0x0800
#define IP_PROTO 6
#define ETH_LEN 14
#include "hdr.h"

typedef struct {
    EthHdr ETH;
    IpHdr IP;
    TCPHdr TCP;
}Packet;


void PrintMAC(char* msg, uint8_t *mac){
    printf("%s : %02x:%02x:%02x:%02x:%02x:%02x \n",msg, mac[0], mac[1],mac[2],mac[3],mac[4],mac[5]);
}

void PrintIP(char* msg, uint32_t ip){
    printf("%s : %d.%d.%d.%d\n",msg, ntohl(ip<<24) & 0xFF, ntohl(ip<<16)&0xFF,ntohl(ip<<8)&0xFF,ntohl(ip)&0xFF);
}

void PrintDATA(char*msg, const u_char*data_loc){
    char* tcp_data = (char*)calloc(10,sizeof(char));
    strncpy(tcp_data, data_loc, 10);
    printf("%s_HEX = ",msg);
    for(int i=0; i<10; i++)
        printf("%x ",tcp_data[i]);

    printf("\n%s_CHAR = ",msg);
    for(int i=0; i<10; i++)
        printf("%c",(char)tcp_data[i]);
    free(tcp_data);
}

void PrintInfo(const u_char* data){
    Packet* packet = (Packet*)data;
    uint16_t Offset;
    if(ntohs(packet->ETH.type) == ETH_TYPE){
        if(ntohs(packet->IP.Protocol == IP_PROTO)){
            // eth src, des mac
            PrintMAC("Source MAC",packet->ETH.Src_mac);
            PrintMAC("Destination MAC",packet->ETH.Des_mac);
            // IP src, des ip
            PrintIP("Source IP", packet->IP.Src_ip);
            PrintIP("Destination IP", packet->IP.Des_ip);
            // tcp src, des port
            printf("Source Port %d\n",ntohs(packet->TCP.Src_port));
            printf("Destination Port %d\n",ntohs(packet->TCP.Des_port));
            //tcp payload maximun 10
            Offset = ntohs(packet->IP.Total_len) - (packet->IP.Hl + packet->TCP.Offset)*4;
            if(Offset >0)
                // data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset) : TCP payload start point
                PrintDATA("DATA",(data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset));
            else
                printf("DATA = 00 00 00 00 00 00 00 00 00 00");
            printf("\n==============================================================\n");
        }
    }
}
