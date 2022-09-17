#pragma once
// MESSAGE KEY PACKING

#define MAVLINK_MSG_ID_KEY 1111


typedef struct __mavlink_key_t {
 uint64_t timestamp; /*<  the time since it start*/
 int16_t i; /*<  just int*/
 char k[32]; /*<  we got the key*/
} mavlink_key_t;

#define MAVLINK_MSG_ID_KEY_LEN 42
#define MAVLINK_MSG_ID_KEY_MIN_LEN 42
#define MAVLINK_MSG_ID_1111_LEN 42
#define MAVLINK_MSG_ID_1111_MIN_LEN 42

#define MAVLINK_MSG_ID_KEY_CRC 245
#define MAVLINK_MSG_ID_1111_CRC 245

#define MAVLINK_MSG_KEY_FIELD_K_LEN 32

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_KEY { \
    1111, \
    "KEY", \
    3, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_key_t, timestamp) }, \
         { "k", NULL, MAVLINK_TYPE_CHAR, 32, 10, offsetof(mavlink_key_t, k) }, \
         { "i", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_key_t, i) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_KEY { \
    "KEY", \
    3, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_key_t, timestamp) }, \
         { "k", NULL, MAVLINK_TYPE_CHAR, 32, 10, offsetof(mavlink_key_t, k) }, \
         { "i", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_key_t, i) }, \
         } \
}
#endif

/**
 * @brief Pack a key message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  the time since it start
 * @param k  we got the key
 * @param i  just int
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_key_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, const char *k, int16_t i)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_KEY_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_int16_t(buf, 8, i);
    _mav_put_char_array(buf, 10, k, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_KEY_LEN);
#else
    mavlink_key_t packet;
    packet.timestamp = timestamp;
    packet.i = i;
    mav_array_memcpy(packet.k, k, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_KEY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_KEY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
}

/**
 * @brief Pack a key message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp  the time since it start
 * @param k  we got the key
 * @param i  just int
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_key_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,const char *k,int16_t i)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_KEY_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_int16_t(buf, 8, i);
    _mav_put_char_array(buf, 10, k, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_KEY_LEN);
#else
    mavlink_key_t packet;
    packet.timestamp = timestamp;
    packet.i = i;
    mav_array_memcpy(packet.k, k, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_KEY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_KEY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
}

/**
 * @brief Encode a key struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param key C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_key_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_key_t* key)
{
    return mavlink_msg_key_pack(system_id, component_id, msg, key->timestamp, key->k, key->i);
}

/**
 * @brief Encode a key struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param key C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_key_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_key_t* key)
{
    return mavlink_msg_key_pack_chan(system_id, component_id, chan, msg, key->timestamp, key->k, key->i);
}

/**
 * @brief Send a key message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp  the time since it start
 * @param k  we got the key
 * @param i  just int
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_key_send(mavlink_channel_t chan, uint64_t timestamp, const char *k, int16_t i)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_KEY_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_int16_t(buf, 8, i);
    _mav_put_char_array(buf, 10, k, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_KEY, buf, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
#else
    mavlink_key_t packet;
    packet.timestamp = timestamp;
    packet.i = i;
    mav_array_memcpy(packet.k, k, sizeof(char)*32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_KEY, (const char *)&packet, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
#endif
}

/**
 * @brief Send a key message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_key_send_struct(mavlink_channel_t chan, const mavlink_key_t* key)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_key_send(chan, key->timestamp, key->k, key->i);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_KEY, (const char *)key, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
#endif
}

#if MAVLINK_MSG_ID_KEY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_key_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, const char *k, int16_t i)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_int16_t(buf, 8, i);
    _mav_put_char_array(buf, 10, k, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_KEY, buf, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
#else
    mavlink_key_t *packet = (mavlink_key_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->i = i;
    mav_array_memcpy(packet->k, k, sizeof(char)*32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_KEY, (const char *)packet, MAVLINK_MSG_ID_KEY_MIN_LEN, MAVLINK_MSG_ID_KEY_LEN, MAVLINK_MSG_ID_KEY_CRC);
#endif
}
#endif

#endif

// MESSAGE KEY UNPACKING


/**
 * @brief Get field timestamp from key message
 *
 * @return  the time since it start
 */
static inline uint64_t mavlink_msg_key_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field k from key message
 *
 * @return  we got the key
 */
static inline uint16_t mavlink_msg_key_get_k(const mavlink_message_t* msg, char *k)
{
    return _MAV_RETURN_char_array(msg, k, 32,  10);
}

/**
 * @brief Get field i from key message
 *
 * @return  just int
 */
static inline int16_t mavlink_msg_key_get_i(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  8);
}

/**
 * @brief Decode a key message into a struct
 *
 * @param msg The message to decode
 * @param key C-struct to decode the message contents into
 */
static inline void mavlink_msg_key_decode(const mavlink_message_t* msg, mavlink_key_t* key)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    key->timestamp = mavlink_msg_key_get_timestamp(msg);
    key->i = mavlink_msg_key_get_i(msg);
    mavlink_msg_key_get_k(msg, key->k);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_KEY_LEN? msg->len : MAVLINK_MSG_ID_KEY_LEN;
        memset(key, 0, MAVLINK_MSG_ID_KEY_LEN);
    memcpy(key, _MAV_PAYLOAD(msg), len);
#endif
}
