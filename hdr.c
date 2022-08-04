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


void PrintMAC(uint8_t *mac){
    printf(" %02x:%02x:%02x:%02x:%02x:%02x |", mac[0], mac[1],mac[2],mac[3],mac[4],mac[5]);
}

void PrintIP(uint32_t ip){
//    printf(" %3d.%3d.%3d.%3d  |", ntohl(ip<<24) & 0xFF, ntohl(ip<<16)&0xFF,ntohl(ip<<8)&0xFF,ntohl(ip)&0xFF);
        printf(" %3d.%3d.%3d.%3d  |", ip&0xFF, (ip>>8)&0xFF, (ip>>16)&0xFF, (ip>>24)&0xFF);
}

void PrintDATA_HEX(const u_char*data_loc){
    char* tcp_data = (char*)calloc(10,sizeof(char));
    strncpy(tcp_data, data_loc, 10);
    printf("  ");
    for(int i=0; i<10; i++)
        printf("%x ",tcp_data[i]);
        printf(" |\n");
    free(tcp_data);
}
void PrintDATA_ASCII(const u_char*data_loc){
    char* tcp_data = (char*)calloc(10,sizeof(char));
    strncpy(tcp_data, data_loc, 10);
    printf("         ASCII : ");
    for(int i=0; i<10; i++)
        printf("%c",(char)tcp_data[i]);
    printf("      |\n");
    free(tcp_data);
}


void PrintInfo(const u_char* data, int cnt){
    Packet* packet = (Packet*)data;
    uint16_t Offset;
    if(ntohs(packet->ETH.type) == ETH_TYPE){
        if(ntohs(packet->IP.Protocol == IP_PROTO)){
            printf("Packet Number = %d\n", cnt);
            printf("---------------------------------------------------------------------------------------------\n");
            printf("|     |        MAC        |        IP        |    PORT    |               DATA              |\n");
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| Src |");
            PrintMAC(packet->ETH.Src_mac);
            PrintIP(packet->IP.Src_ip);
            printf(" %8d   |",ntohs(packet->TCP.Src_port));
            Offset = ntohs(packet->IP.Total_len) - (packet->IP.Hl + packet->TCP.Offset)*4;
            if(Offset >0)
                // data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset) : TCP payload start point
                PrintDATA_HEX((data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset));
            else
                printf("  00 00 00 00 00 00 00 00 00 00  |\n");
            printf("----------------------------------------------------------                                    \n");
            printf("| Des |");
            PrintMAC(packet->ETH.Des_mac);
            PrintIP(packet->IP.Des_ip);
            printf(" %8d   |",ntohs(packet->TCP.Des_port));
            if(Offset >0)
                // data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset) : TCP payload start point
                PrintDATA_ASCII((data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset));
            else
                printf("                                 |\n");
            printf("---------------------------------------------------------------------------------------------\n\n");
        }
    }
}
