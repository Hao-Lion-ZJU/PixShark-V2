/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : mqtt_client.cpp
 * @brief     : mqtt客户端实现,c+++封装LWIP的mqtt应用层接口
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-11-19       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "mqtt_client.hpp"
#include <string.h>
#include<limits>


namespace mqtt
{

Client::Client(const char *id){
    client_ = mqtt_client_new();
    if (client_ == NULL || id == NULL)
    {
        //id  cannot be zero
        configASSERT(0);
    }
    /* Setup an empty client info structure */
    memset(&ci_, 0, sizeof(ci_));
    strcpy(client_id_, id);
    ci_.client_id = client_id_;
}

Client::~Client(){
    mqtt_disconnect(client_);
    client_ = NULL;
}

void Client::username_pw_set(const char* user , const char *password){
    if (user == NULL || password == NULL)
    {
        return;
    }
    strcpy(user_, user);
    strcpy(passw_, password);
    ci_.client_user = user_;
    ci_.client_pass = passw_;
}


bool Client::connect(const char *ip , uint16_t port, uint16_t keepalive, uint32_t timeout){

    err_t err;
    ip_addr_t  ip_mqtt;
    if (ip == NULL)
    {
        return false;
    }
    //字符串转换为ip地址结构体
    err = ip4addr_aton(ip,&ip_mqtt);
    if(!err){
        return false;
    }
    ci_.keep_alive = keepalive;
    do{
        err = mqtt_client_connect(client_, &ip_mqtt, MQTT_PORT, Client::mqtt_connection_cb, this, &ci_);
        if(err != ERR_OK){
            return false;
        }
        osDelay(500);
        timeout--;
        if(timeout == 0){
            return false;
        }
    }while(mqtt_client_is_connected(client_));
    return true;
}


void Client::disconnect(){
    mqtt_disconnect(client_);
}


bool Client::publish(const char *topic, const void *payload, u16_t payload_length, u8_t qos, u8_t retain){
    err_t err;
    if (topic == NULL || payload == NULL || isConnected() == false)
    {
        return false;
    }
    err = mqtt_publish(client_, topic, payload, payload_length, qos, retain, mqtt_pub_request_cb, this);
    if(err != ERR_OK){
        return false;
    }
    return true;
}

bool Client::subscribe(const char *topic, u8_t qos){
    err_t err;
    if (topic == NULL)
    {
        return false;
    }
    err = mqtt_subscribe(client_, topic, qos, mqtt_sub_request_cb, this);
    if(err != ERR_OK){
        return false;
    }
    return true;
}


bool Client::unsubscribe(const char *topic){
    err_t err;
    if (topic == NULL)
    {
        return false;
    }
    err = mqtt_unsubscribe(client_, topic, mqtt_unsub_request_cb, this);
    if(err != ERR_OK){
        return false;
    }
    return true;
}



void Client::mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    err_t err;
    Client* this_client;
    this_client = (Client*)arg;
    //连接成功
    if(status == MQTT_CONNECT_ACCEPTED) {
        mqtt_set_inpub_callback(this_client->client_, this_client->on_message_, this_client->on_data_, arg);
    } else {
        //连接失败
        mqtt_disconnect(this_client->client_);
    }
}


void Client::mqtt_pub_request_cb(void *arg, err_t result)
{
    Client* this_client;
    this_client = (Client*)arg;
    if(this_client->on_publish_ != nullptr)
    {
        
        this_client->on_publish_(this_client, result); 
    }  

}

void Client::mqtt_sub_request_cb(void *arg, err_t result)
{
    Client* this_client;
    this_client = (Client*)arg;
    if(this_client->on_subscribe_ != nullptr)
    {
        this_client->on_subscribe_(this_client, result); 
    }
}

void Client::mqtt_unsub_request_cb(void *arg, err_t result)
{
    Client* this_client;
    this_client = (Client*)arg;
    if(this_client->on_unsubscribe_ != nullptr)
    {
        this_client->on_unsubscribe_(this_client, result); 
    }
}

}