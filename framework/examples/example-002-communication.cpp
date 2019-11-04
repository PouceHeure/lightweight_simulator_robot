
#include "communication/publisher.hpp"
#include "communication/handle_communication.hpp"

#include <iostream>

void callback(int value){
    std::cout << "value received: " << value << std::endl;
}

void callback_str(std::string value){
    std::cout << "value received: " << value << std::endl;
}


int main(int argc,char** argv){
    HandleCommunication* hc = new HandleCommunication();
    
    Publisher<int>* pub0 = hc->createPublisher<int>("chatter");
    Publisher<int>* pub1 = hc->createPublisher<int>("chatter");

    Subscriber<int>* sub0 = hc->createSubscriber<int>("chatter",callback);
    Subscriber<int>* sub1 = hc->createSubscriber<int>("chatter",callback);
    Subscriber<int>* sub2 = hc->createSubscriber<int>("chatter",callback);
    Subscriber<int>* sub3 = hc->createSubscriber<int>("chatter",callback);

    Publisher<std::string>* pubStr = hc->createPublisher<std::string>("chatter_string");

    Subscriber<std::string>* subStr0 = hc->createSubscriber<std::string>("chatter_string",callback_str);
    Subscriber<std::string>* subStr1 = hc->createSubscriber<std::string>("chatter_string",callback_str);
    Subscriber<std::string>* subStr2 = hc->createSubscriber<std::string>("chatter_string",callback_str);
    Subscriber<std::string>* subStr3 = hc->createSubscriber<std::string>("chatter_string",callback_str);

    std::cout << "\n## pub0 | chatter | 15 \n" << std::endl;
    pub0->publish(15);
    std::cout << "\n## pub1 | chatter | -1 \n" << std::endl;
    pub1->publish(-1);
    std::cout << "\n## pubstr | chatter_str | bonjour \n" << std::endl;
    pubStr->publish("bonjour");

    return 0;
}