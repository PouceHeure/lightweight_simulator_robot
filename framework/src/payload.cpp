
/**
 * @file payload.cpp
 * @author Hugo POUSSEUR
 * @brief 
 * @version 0.1
 * @date 2019-10-31
 */

#include<recorder/payload.hpp>

// utils methods 
void payload::printBytes(const void *object, size_t size)
{
  const unsigned char * const bytes = static_cast<const unsigned char *>(object);
  size_t i;
  printf("payload: [ ");
  for(i = 0; i < size; i++){
    printf("%02x ", bytes[i]);
  }
  printf("]\n");
}


// findTypeCode specialization 
template<>
int payload::findTypeCode<int>(){
    return CODE_TYPE_INT;
}

template<>
int payload::findTypeCode<long>(){
    return CODE_TYPE_LONG;
}

template<>
int payload::findTypeCode<uint>(){
    return CODE_TYPE_UINT;
}

template<>
int payload::findTypeCode<ulong>(){
    return CODE_TYPE_ULONG;
}

template<>
int payload::findTypeCode<float>(){
    return CODE_TYPE_FLOAT;
}

template<>
int payload::findTypeCode<std::string>(){
    return CODE_TYPE_STRING;
}

template<>
int payload::findTypeCode<const char*>(){
    return CODE_TYPE_CHARSTR;
}


// decode methods
void payload::decodeHeader(int& type, int &length,char * buffer){
    type = int(buffer[0]);
    length = int(buffer[LEN_0_TYPE]);
}

template<>
std::string payload::decodeValue(char* buffer, int size){
    return std::string(buffer,size);
}

// encode methods
template<>
void payload::encodeValueContent(char* buffer,std::string value,int size){
    memcpy (&buffer[LEN_0_TYPE+LEN_1_LENGTH+LEN_3_TICK],value.c_str(),size);
}

template<>
int payload::encodeValueSize(std::string value){
    return value.size()*sizeof(char);
}





