// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from underwater_robot_msgs:msg/Altimeter.idl
// generated code does not contain a copyright notice

#ifndef UNDERWATER_ROBOT_MSGS__MSG__DETAIL__ALTIMETER__STRUCT_H_
#define UNDERWATER_ROBOT_MSGS__MSG__DETAIL__ALTIMETER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Altimeter in the package underwater_robot_msgs.
typedef struct underwater_robot_msgs__msg__Altimeter
{
  /// height
  float height;
  /// correlation factor
  float correlation;
} underwater_robot_msgs__msg__Altimeter;

// Struct for a sequence of underwater_robot_msgs__msg__Altimeter.
typedef struct underwater_robot_msgs__msg__Altimeter__Sequence
{
  underwater_robot_msgs__msg__Altimeter * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} underwater_robot_msgs__msg__Altimeter__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UNDERWATER_ROBOT_MSGS__MSG__DETAIL__ALTIMETER__STRUCT_H_
