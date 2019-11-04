#include "recorder/server.hpp"



Server::Server(int port,std::string _address){
    int opt = 1; 
    int addrlen = sizeof(address); 
    

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        // add error
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        // add error
    } 
    
    address.sin_family = AF_INET;  
    struct hostent *host_entity = gethostbyname(_address.c_str());
    address.sin_addr.s_addr = *(ulong*) host_entity->h_addr_list[0];
    address.sin_port = htons( port ); 
       
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
       // add error
    } 
    
    mThread = std::thread(&Server::listenNewConnection,this);
}


void Server::advertiseNewRecorder(IRecorder* recorder)
{
    register_recorders.insert({recorder,std::vector<int>()});
}


void Server::listenNewConnection(){

    char header[4];
    while(true){
        if (listen(server_fd, -1) < 0) { 
            std::cerr << "error listen" << std::endl;
        } 
        // !! need to declare socken_t value !! 
        socklen_t addr_size = sizeof(address);
        int new_socket = accept(server_fd, (struct sockaddr *)&address, &addr_size);
        
        if(new_socket < 0){
            std::cerr << "error socket" << std::endl;
        }

        // read header (size and type)
        read(new_socket, header, 4);
        int size;
        int type;
        payload::decodeHeader(type,size,header);
        // read content (tick and value)
        int tick;
        char* content = (char*)malloc(sizeof(char*) * (size));
        read(new_socket, content, size);
        std::string value_find = payload::decodeContent<std::string>(tick,content,size);
        free(content);  
        std::cout << "request: " << value_find << std::endl;
        std::map<IRecorder*, std::vector<int>>::iterator it_register;
        for(it_register = register_recorders.begin(); it_register != register_recorders.end(); ++it_register)
        {
            
            if(!strcmp(value_find.c_str(),it_register->first->getName().c_str())){
                std::cout << "request: " << value_find << " accepted" << std::endl;
                it_register->second.push_back(new_socket);
                break;
            }
        }
    }

}