#pragma once
#include <stdint.h>

#pragma pack(push, 1)
typedef struct{
    uint8_t Des_mac[6];
    uint8_t Src_mac[6];
    uint16_t type;
}EthHdr;
typedef struct{
    uint8_t Hl:4;       // Follow Bit Order (Not Byte Order)
    uint8_t Verison:4;
    uint8_t Tos;
    uint16_t Total_len;
    uint16_t Id;
    uint16_t Frag_off;
    uint8_t TTL;
    uint8_t Protocol;
    uint16_t Check;
    uint32_t Src_ip;
    uint32_t Des_ip;
}IpHdr;
typedef struct{
    uint16_t Src_port;
    uint16_t Des_port;
    uint32_t Seq_num;
    uint32_t Ack_num;
    uint8_t Reverse_NG:4;   // Follow Bit Order (Not Byte Order)
    uint8_t Offset:4;
    uint8_t Flag;
    uint16_t Window;
    uint16_t Checksum;
    uint16_t Urgent;
}TCPHdr;
#pragma pack(pop)

void PrintMAC(uint8_t *mac);

void PrintIP(uint32_t ip);

void PrintDATA_HEX(const u_char*data_loc);

void PrintDATA_ASCII(const u_char*data_loc);

void PrintSrc(uint8_t *mac, uint32_t ip, uint16_t port, const u_char* data, uint16_t Offset);

void PrintDst(uint8_t *mac, uint32_t ip, uint16_t port,const u_char* data,uint16_t Offset);

void PrintInfo(const u_char* data, int cnt);
