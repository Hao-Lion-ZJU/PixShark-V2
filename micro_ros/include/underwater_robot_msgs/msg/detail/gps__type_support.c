// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from underwater_robot_msgs:msg/Gps.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "underwater_robot_msgs/msg/detail/gps__rosidl_typesupport_introspection_c.h"
#include "underwater_robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "underwater_robot_msgs/msg/detail/gps__functions.h"
#include "underwater_robot_msgs/msg/detail/gps__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  underwater_robot_msgs__msg__Gps__init(message_memory);
}

void underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_fini_function(void * message_memory)
{
  underwater_robot_msgs__msg__Gps__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_member_array[2] = {
  {
    "latitude",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(underwater_robot_msgs__msg__Gps, latitude),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "longitude",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(underwater_robot_msgs__msg__Gps, longitude),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_members = {
  "underwater_robot_msgs__msg",  // message namespace
  "Gps",  // message name
  2,  // number of fields
  sizeof(underwater_robot_msgs__msg__Gps),
  underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_member_array,  // message members
  underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_init_function,  // function to initialize message memory (memory has to be allocated)
  underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_type_support_handle = {
  0,
  &underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_underwater_robot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, underwater_robot_msgs, msg, Gps)() {
  if (!underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_type_support_handle.typesupport_identifier) {
    underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &underwater_robot_msgs__msg__Gps__rosidl_typesupport_introspection_c__Gps_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
