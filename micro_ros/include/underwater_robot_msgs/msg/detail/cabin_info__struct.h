// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from underwater_robot_msgs:msg/CabinInfo.idl
// generated code does not contain a copyright notice

#ifndef UNDERWATER_ROBOT_MSGS__MSG__DETAIL__CABIN_INFO__STRUCT_H_
#define UNDERWATER_ROBOT_MSGS__MSG__DETAIL__CABIN_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CabinInfo in the package underwater_robot_msgs.
typedef struct underwater_robot_msgs__msg__CabinInfo
{
  /// temperature in cabin
  float temperature;
  /// humidity in cabin
  float humidity;
  /// water_level in cabin
  float water_level;
  /// CPU temperature
  float cpu_temperature;
} underwater_robot_msgs__msg__CabinInfo;

// Struct for a sequence of underwater_robot_msgs__msg__CabinInfo.
typedef struct underwater_robot_msgs__msg__CabinInfo__Sequence
{
  underwater_robot_msgs__msg__CabinInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} underwater_robot_msgs__msg__CabinInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UNDERWATER_ROBOT_MSGS__MSG__DETAIL__CABIN_INFO__STRUCT_H_
