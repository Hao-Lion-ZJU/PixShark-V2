// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from example_interfaces:msg/Float32MultiArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "example_interfaces/msg/detail/float32_multi_array__rosidl_typesupport_introspection_c.h"
#include "example_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "example_interfaces/msg/detail/float32_multi_array__functions.h"
#include "example_interfaces/msg/detail/float32_multi_array__struct.h"


// Include directives for member types
// Member `layout`
#include "example_interfaces/msg/multi_array_layout.h"
// Member `layout`
#include "example_interfaces/msg/detail/multi_array_layout__rosidl_typesupport_introspection_c.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  example_interfaces__msg__Float32MultiArray__init(message_memory);
}

void example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_fini_function(void * message_memory)
{
  example_interfaces__msg__Float32MultiArray__fini(message_memory);
}

size_t example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__size_function__Float32MultiArray__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__get_const_function__Float32MultiArray__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__get_function__Float32MultiArray__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__fetch_function__Float32MultiArray__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__get_const_function__Float32MultiArray__data(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__assign_function__Float32MultiArray__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__get_function__Float32MultiArray__data(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__resize_function__Float32MultiArray__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_member_array[2] = {
  {
    "layout",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(example_interfaces__msg__Float32MultiArray, layout),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(example_interfaces__msg__Float32MultiArray, data),  // bytes offset in struct
    NULL,  // default value
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__size_function__Float32MultiArray__data,  // size() function pointer
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__get_const_function__Float32MultiArray__data,  // get_const(index) function pointer
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__get_function__Float32MultiArray__data,  // get(index) function pointer
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__fetch_function__Float32MultiArray__data,  // fetch(index, &value) function pointer
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__assign_function__Float32MultiArray__data,  // assign(index, value) function pointer
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__resize_function__Float32MultiArray__data  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_members = {
  "example_interfaces__msg",  // message namespace
  "Float32MultiArray",  // message name
  2,  // number of fields
  sizeof(example_interfaces__msg__Float32MultiArray),
  example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_member_array,  // message members
  example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_init_function,  // function to initialize message memory (memory has to be allocated)
  example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_type_support_handle = {
  0,
  &example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_example_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, example_interfaces, msg, Float32MultiArray)() {
  example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, example_interfaces, msg, MultiArrayLayout)();
  if (!example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_type_support_handle.typesupport_identifier) {
    example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &example_interfaces__msg__Float32MultiArray__rosidl_typesupport_introspection_c__Float32MultiArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
