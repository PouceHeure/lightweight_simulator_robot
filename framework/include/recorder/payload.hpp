#pragma once 

/**
 * @file payload.hpp
 * @author Hugo POUSSEUR
 * @brief Store methods used for encode and decode payload
 * A namespace encapsulates these methods. 
 * @version 0.1
 * @date 2019-11-04
 */

#include <string>

#include <stdio.h>      // Default System Calls
#include <stdlib.h>     // Needed for OS X
#include <string.h>     // Needed for Strlen
#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <time.h>       // To control the timeout mechanism
#include <unistd.h>
#include <iostream>

// payload space allocated for each static value 
#define LEN_0_TYPE 2
#define LEN_1_LENGTH 2 
#define LEN_2_LENGHT_OPT 2 //no implemented yet 
#define LEN_3_TICK 4

// code associated to each type 
// new code implicated a new specialization ! 
#define CODE_TYPE_ERROR -1
#define CODE_TYPE_NO_DATA 0
#define CODE_TYPE_INT 3
#define CODE_TYPE_LONG 2
#define CODE_TYPE_UINT 1 
#define CODE_TYPE_ULONG 4
#define CODE_TYPE_STRING 6
#define CODE_TYPE_CHARSTR 7
#define CODE_TYPE_FLOAT 9 

namespace payload {

    // utils methods
    void printBytes(const void *object, size_t size);

    // findTypeCode method and declaration specialization 
    template<typename T>
    int findTypeCode(){
        return CODE_TYPE_ERROR;
    }

    template<>
    int findTypeCode<int>();

    template<>
    int findTypeCode<long>();

    template<>
    int findTypeCode<uint>();

    template<>
    int findTypeCode<ulong>();

    template<>
    int findTypeCode<float>();

    template<>
    int findTypeCode<const char *>();

    template<>
    int findTypeCode<std::string>();

    // decode methods
    void decodeHeader(int& type, int &length,char * buffer);

    template<typename T>
    T decodeValue(char* buffer,int size){
        T value;
        memcpy(&value, &buffer[0], size);
        return value;
    }

    template<>
    std::string decodeValue(char* buffer, int size);

    template<typename T>
    T decodeContent(int &tick,char* buffer,int size){
        tick = int(buffer[0]);
        char* buffer_content = &buffer[LEN_3_TICK];
        T value = decodeValue<T>(buffer_content,size-LEN_3_TICK);
        return value;
    }

    // encode methods 
    template<typename T>
    void encodeValueContent(char* buffer, T value,int size){
        memcpy(&buffer[LEN_0_TYPE+LEN_1_LENGTH+LEN_3_TICK],&value,size);
    }

    template<>
    void encodeValueContent(char* buffer, std::string value,int size);

    template<typename T>
    int encodeValueSize(T value){
       return sizeof(value);
    }

    template<>
    int encodeValueSize(std::string value);

    /**
     * @brief Encode the tick and value data 
     * Be carefull, if you use this method, please check method: 
     *  - encodeValueSize 
     *  - encodeValue
     * @tparam T type of value 
     * @param size the buffer size
     * @param tick the current tick simulation  
     * @param value the value to send 
     * @return char* 
     */
    template<typename T>
    char* encode(int& size, int tick,T value){
        // the way to compute the size can be different, for example string 
        int value_size = encodeValueSize<T>(value);
        size = LEN_0_TYPE+LEN_1_LENGTH+LEN_3_TICK + value_size;
        int length = value_size + sizeof(tick);
        int type = findTypeCode<T>();
        char* buffer = (char*)malloc( sizeof(char*) * (size));
        memcpy (&buffer[0],&type,LEN_0_TYPE);
        memcpy (&buffer[LEN_0_TYPE],&length,LEN_1_LENGTH);
        memcpy (&buffer[LEN_0_TYPE+LEN_1_LENGTH],&tick,LEN_3_TICK);
        // the way to encode value can be different, for example string 
        encodeValueContent<T>(buffer,value,value_size);
        return buffer;
    }
};

 
