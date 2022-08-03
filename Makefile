CC = gcc
OBJS = main.o hdr.o
TARGET = pcap-test

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lpcap
	rm *.o

main.o: hdr.h main.c

hdr.o: hdr.h hdr.c

clean:
	rm -rf *.o $(TARGET)
