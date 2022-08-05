#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "hdr.h"
#define ETH_TYPE 0x0800
#define IP_PROTO 6
#define ETH_LEN 14

typedef struct {
    EthHdr ETH;
    IpHdr IP;
    TCPHdr TCP;
}Packet;


void PrintMAC(uint8_t *mac){
    printf(" %02x:%02x:%02x:%02x:%02x:%02x |", mac[0], mac[1],mac[2],mac[3],mac[4],mac[5]);
}

void PrintIP(uint32_t ip){
        printf(" %3d.%3d.%3d.%3d  |", ip&0xFF, (ip>>8)&0xFF, (ip>>16)&0xFF, (ip>>24)&0xFF);
}

void PrintDATA_HEX(const u_char*data_loc){
    char* tcp_data = (char*)calloc(10,sizeof(char));
    if(tcp_data == NULL){
        fprintf(stderr,"Memory Allocation Error\n");
        exit(-1);
    }
    strncpy(tcp_data, data_loc, 10);
    printf("  ");
    for(int i=0; i<10; i++)
        printf("%x ",tcp_data[i]);
        printf(" |\n");
    free(tcp_data);
}

void PrintDATA_ASCII(const u_char*data_loc){
    char* tcp_data = (char*)calloc(10,sizeof(char));
    if(tcp_data == NULL){
        fprintf(stderr,"Memory Allocation Error\n");
        exit(-1);
    }
    strncpy(tcp_data, data_loc, 10);
    printf("         ASCII : ");
    for(int i=0; i<10; i++)
        printf("%c",(char)tcp_data[i]);
    printf("      |\n");
    free(tcp_data);
}

void PrintSrc(uint8_t *mac, uint32_t ip, uint16_t port,const u_char* data,uint16_t Offset){
    printf("| Src |");
    PrintMAC(mac);
    PrintIP(ip);
    printf(" %8d   |",ntohs(port));
    if(Offset >0)
        PrintDATA_HEX(data);
    else
        printf("              NO DATA            |\n");
    printf("----------------------------------------------------------                                    \n");
}

void PrintDst(uint8_t *mac, uint32_t ip, uint16_t port,const u_char* data,uint16_t Offset){
    printf("| Dst |");
    PrintMAC(mac);
    PrintIP(ip);
    printf(" %8d   |",ntohs(port));
    if(Offset >0)
        PrintDATA_ASCII(data);
    else
        printf("                                 |\n");
    printf("---------------------------------------------------------------------------------------------\n\n");
}

void PrintInfo(const u_char* data, int cnt){
    Packet* packet = (Packet*)data;
    uint16_t Offset = ntohs(packet->IP.Total_len) - (packet->IP.Hl + packet->TCP.Offset)*4;;
    if(ntohs(packet->ETH.type) == ETH_TYPE){
        if(ntohs(packet->IP.Protocol == IP_PROTO)){
            printf("Packet Number = %d\n", cnt);
            printf("---------------------------------------------------------------------------------------------\n");
            printf("|     |        MAC        |        IP        |    PORT    |               DATA              |\n");
            printf("---------------------------------------------------------------------------------------------\n");
            // data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset) : TCP payload start point
            PrintSrc(packet->ETH.Src_mac, packet->IP.Src_ip, packet->TCP.Src_port, (data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset),Offset);
            PrintDst(packet->ETH.Des_mac, packet->IP.Des_ip, packet->TCP.Des_port, (data+(ETH_LEN+ntohs(packet->IP.Total_len))-Offset),Offset);
        }
    }
}
