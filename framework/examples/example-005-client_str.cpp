
// C client code to send string to reverse 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <iostream>  

#include <recorder/payload.hpp>

#define PORT 8090 
  
// Driver code 
int main() 
{ 
    struct sockaddr_in address; 
    struct sockaddr_in serv_addr; 
    int sock = 0; 
  
    if ((sock = socket(AF_INET, 
                       SOCK_STREAM, 0)) 
        < 0) { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
  
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(12345); 
  
    if (inet_pton(AF_INET, "127.0.0.1", 
                  &serv_addr.sin_addr) 
        <= 0) { 
        printf("\nAddress not supported \n"); 
        return -1; 
    } 
  
    // connect the socket 
    if (connect(sock, (struct sockaddr*)&serv_addr, 
                sizeof(serv_addr)) 
        < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
  
    int size; 
    std::string target = "r_test_str";
    char* buffer = payload::encode<std::string>(size,0,target);

    // send string to server side 
    send(sock, buffer, size, 0); 
    int counter_rcv = 0;
    char header[4];
    while(true){
        // read header
        if(recv(sock, header, size_t(4),0) < 0){
          std::cerr << "fail" << std::endl;
          break;
        }
        std::cout << "counter: " << counter_rcv++ << std::endl;
        int size;
        int type;
        payload::decodeHeader(type,size,header);
        payload::printBytes(header,4);
        std::cout << "size: " << size << std::endl;
        std::cout << "type: " << type << std::endl;
        // read content (tick and value)
        int tick;
        char* content = (char*)malloc(sizeof(char*) * (size + 1 ));
        
        if(recv(sock, content, size_t(size),0) <0){
          std::cerr << "fail" << std::endl;
          break;
        }
        payload::printBytes(content, size); 
        std::string value = payload::decodeContent<std::string>(tick,content,size);
        free(content); 
        std::cout << "tick: " << tick << std::endl; 
        std::cout << "value: " << value << std::endl; 
        printf("\n");
    }
    return 0; 
} 
