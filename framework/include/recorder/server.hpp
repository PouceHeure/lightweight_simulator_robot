#pragma once 

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <map>
#include <netdb.h>
#include <thread>
#include <cstring>

#include <recorder/recorder.hpp>
#include <recorder/payload.hpp>


#define LEN_0_TYPE 2
#define LEN_1_LENGTH 2 
#define LEN_2_TICK 4 

class Server {
    private: 
        int server_fd;
        struct sockaddr_in address;

        std::thread mThread;

        std::map<IRecorder*,std::vector<int>> register_recorders;

        void listenNewConnection();
        
        template<typename T>
        int findTypeCode();

        template<typename T>
        char* createPayload(int type, int tick,T value,int& size);

    public:
        Server(int port,std::string address);

        void advertiseNewRecorder(IRecorder* recorder);

        template<typename T>
        void sendValue(IRecorder *recorder, int tick, T value);

};




template<typename T>
void Server::sendValue(IRecorder *recorder,int tick,T value){
    // get sockets from map 
    std::vector<int> sockets_clients = register_recorders[recorder];
    
    // no socket, it's useless to create payload 
    if(sockets_clients.size() == 0){
        return;
    }

    int length;
    char * buffer = payload::encode<T>(length,tick,value);

    std::vector<int>::iterator it_sockets;
    for(it_sockets = sockets_clients.begin();it_sockets != sockets_clients.end();++it_sockets){
       
        if(send(*it_sockets, buffer, length, 0 )){
            std::cerr << "failed to send" << std::endl;
        }
    }
    // free buffer allocated 
    free(buffer);
}