#pragma once

/**
 * @file handle_communication.hpp
 * @author Hugo POUSSEUR
 * @brief Definition of HandleCommunication class 
 * @version 0.1
 * @date 2019-10-31
 */

#include "communication/topic.hpp"
#include "communication/interacter.hpp"
#include "communication/subscriber.hpp"
#include "communication/publisher.hpp"

#include <map>
#include <boost/bind.hpp>
#include <boost/function.hpp>



/**
 * @brief Handle the communication, allows to handle subscriber and publisher
 * 
 */
class HandleCommunication {
    private: 
        std::map<std::string,ITopic*> topics;

    public: 

        /**
         * @brief Declare new subscriber or publisher to the handle communication.
         * If the topic hasn't been created yet, it's created 
         * 
         * @tparam T_MSG 
         * @param interactor subscriber or publisher pointer 
         * @return Topic<T_MSG>* Topic topic attached
         */
        template <typename T_MSG>
        Topic<T_MSG>* declareNewInteracter(Interacter<T_MSG>* interactor);
        
        /**
         * @brief Create a Subscriber object
         * 
         * @tparam T_MSG 
         * @param topic_name the topic name used by the subscriber
         * @param callback callback called at each data reception 
         * @return Subscriber<T_MSG>* 
         */
        template <typename T_MSG>
        Subscriber<T_MSG>* createSubscriber(std::string topic_name, boost::function<void(T_MSG)> callback);

        /**
         * @brief Create a Publisher object
         * 
         * @tparam T_MSG 
         * @param topic_name the topic name used by the subscriber 
         * @return Publisher<T_MSG>* 
         */
        template <typename T_MSG>
        Publisher<T_MSG>* createPublisher(std::string topic_name);

        /**
         * @brief Inform that a new message has been published in the topic 
         * 
         * @tparam T_MSG 
         * @param topic 
         * @param msg 
         */
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
    // check if the topic has been already created
    if(topics.find(topic_name) == topics.end() ) {
        // if not, the topic is created
        Topic<T_MSG>* new_topic = new Topic<T_MSG>(topic_name);
        topics.insert({topic_name,new_topic});
        return new_topic;
    }
    return static_cast<Topic<T_MSG>*>(topics.at(topic_name));
}


template <typename T_MSG>
Publisher<T_MSG>* HandleCommunication::createPublisher(std::string topic_name){
    // create the publisher 
    Publisher<T_MSG>* pub = new Publisher<T_MSG>(topic_name);
    Topic<T_MSG>* topic = declareNewInteracter(pub);
    // create method that is called at each publication 
    boost::function<void(T_MSG)> request = boost::bind(&HandleCommunication::trigPublishNewMsg<T_MSG>,
                                                                this,topic,_1);
    // attach the method                                                                  
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
