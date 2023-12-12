#ifndef _MQTT_CLIENT_HPP_
#define _MQTT_CLIENT_HPP_




#ifdef __cplusplus
extern "C" {
#endif
#include "lwip/apps/mqtt.h"

#ifdef __cplusplus
}
#endif

#include "common.hpp"

namespace mqtt
{



class Client
{
public:
    Client(const char *id);
    ~Client();

    void username_pw_set(const char* user = " ", const char *password = " ");

    bool connect(const char *ip , uint16_t port = MQTT_PORT, uint16_t keepalive = 0, uint32_t timeout = 0xffff);

    void disconnect();
    /**
     * @brief mqtt 发布话题
     * @param topic 话题
     * @param payload 消息内容
     * @param payload_length 消息长度
     * @param qos 消息质量  0：最多一次 1：至少一次 2：只有一次，失败会重新传输
    */
    bool publish(const char *topic, const void *payload, u16_t payload_length, u8_t qos = 0, u8_t retain = 0);

    /**
     * @brief mqtt 订阅话题
     * @param topic 话题
     * @param qos 消息质量  0：最多一次 1：至少一次 2：只有一次，失败会重新传输
    */
    bool subscribe(const char *topic, u8_t qos = 0);

    /**
     * @brief mqtt 取消订阅话题
     * @param topic 话题
    */
    bool unsubscribe(const char *topic);

    bool isConnected(){
        return mqtt_client_is_connected(client_);
    }   

    void(*on_publish_)(void *this_client, err_t result) = nullptr;

    void(*on_subscribe_)(void *this_client, err_t result) = nullptr;

    void(*on_unsubscribe_)(void *this_client, err_t result) = nullptr;

    void(*on_message_)(void *this_client, const char *topic, u32_t tot_len) = nullptr;

    void(*on_data_)(void *this_client, const u8_t *data, u16_t len, u8_t flags) = nullptr;





private:
    static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);

    static void mqtt_pub_request_cb(void *arg, err_t result);

    static void mqtt_sub_request_cb(void *arg, err_t result);

    static void mqtt_unsub_request_cb(void *arg, err_t result);



	mqtt_client_t *client_;
    char client_id_[16];
    char user_[16];
    char passw_[16];
    struct mqtt_connect_client_info_t ci_;

};

}
#endif /* _MQTT_CLIENT_HPP_ */
