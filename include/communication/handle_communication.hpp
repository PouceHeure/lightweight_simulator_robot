#pragma once

#include <map>
#include "communication/topic.hpp"
#include "communication/interacter.hpp"
#include "communication/subscriber.hpp"
#include "communication/publisher.hpp"

#include <boost/bind.hpp>
#include <boost/function.hpp>



class HandleCommunication {
    private: 
        std::map<std::string,ITopic*> topics;

    public: 
        template <typename T_MSG>
        Topic<T_MSG>* declareNewInteracter(Interacter<T_MSG>* interactor);
        
        template <typename T_MSG>
        Subscriber<T_MSG>* createSubscriber(std::string topic_name, boost::function<void(T_MSG)> callback);

        template <typename T_MSG>
        Publisher<T_MSG>* createPublisher(std::string topic_name);

        template <typename T_MSG>
        void trigPublishNewMsg(Topic<T_MSG> *topic,T_MSG msg);
        

};

template <typename T_MSG>
void HandleCommunication::trigPublishNewMsg(Topic<T_MSG> *topic,T_MSG msg){
    if(topic != nullptr){
        topic->broadcast(msg);
    }
}

template <typename T_MSG>
Topic<T_MSG>* HandleCommunication::declareNewInteracter(Interacter<T_MSG>* interactor){
    std::string topic_name = interactor->getTopicName(); 
    if(topics.find(topic_name) == topics.end() ) {
        Topic<T_MSG>* new_topic = new Topic<T_MSG>(topic_name);
        topics.insert({topic_name,new_topic});
        return new_topic;
    }
    return static_cast<Topic<T_MSG>*>(topics.at(topic_name));
}


template <typename T_MSG>
Publisher<T_MSG>* HandleCommunication::createPublisher(std::string topic_name){
    Publisher<T_MSG>* pub = new Publisher<T_MSG>(topic_name);
    Topic<T_MSG>* topic = declareNewInteracter(pub);
    boost::function<void(T_MSG)> request = boost::bind(&HandleCommunication::trigPublishNewMsg<T_MSG>,
                                                                this,topic,_1); 
    pub->attachPublishMethod(request);
    return pub;
}

template <typename T_MSG>
Subscriber<T_MSG>* HandleCommunication::createSubscriber(std::string topic_name, boost::function<void(T_MSG)> callback){
    Subscriber<T_MSG>* sub = new Subscriber<T_MSG>(topic_name,callback);
    Topic<T_MSG>* topic = declareNewInteracter(sub);
    topic->addSubscriber(*sub);
    return sub;
}
