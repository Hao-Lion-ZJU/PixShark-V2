// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rcl_interfaces:srv/SetParameters.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rcl_interfaces/srv/detail/set_parameters__rosidl_typesupport_introspection_c.h"
#include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rcl_interfaces/srv/detail/set_parameters__functions.h"
#include "rcl_interfaces/srv/detail/set_parameters__struct.h"


// Include directives for member types
// Member `parameters`
#include "rcl_interfaces/msg/parameter.h"
// Member `parameters`
#include "rcl_interfaces/msg/detail/parameter__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetParameters_Request__init(message_memory);
}

void rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetParameters_Request__fini(message_memory);
}

size_t rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__size_function__SetParameters_Request__parameters(
  const void * untyped_member)
{
  const rcl_interfaces__msg__Parameter__Sequence * member =
    (const rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__get_const_function__SetParameters_Request__parameters(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__msg__Parameter__Sequence * member =
    (const rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__get_function__SetParameters_Request__parameters(
  void * untyped_member, size_t index)
{
  rcl_interfaces__msg__Parameter__Sequence * member =
    (rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__fetch_function__SetParameters_Request__parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__msg__Parameter * item =
    ((const rcl_interfaces__msg__Parameter *)
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__get_const_function__SetParameters_Request__parameters(untyped_member, index));
  rcl_interfaces__msg__Parameter * value =
    (rcl_interfaces__msg__Parameter *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__assign_function__SetParameters_Request__parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__msg__Parameter * item =
    ((rcl_interfaces__msg__Parameter *)
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__get_function__SetParameters_Request__parameters(untyped_member, index));
  const rcl_interfaces__msg__Parameter * value =
    (const rcl_interfaces__msg__Parameter *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__resize_function__SetParameters_Request__parameters(
  void * untyped_member, size_t size)
{
  rcl_interfaces__msg__Parameter__Sequence * member =
    (rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  rcl_interfaces__msg__Parameter__Sequence__fini(member);
  return rcl_interfaces__msg__Parameter__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_member_array[1] = {
  {
    "parameters",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParameters_Request, parameters),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__size_function__SetParameters_Request__parameters,  // size() function pointer
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__get_const_function__SetParameters_Request__parameters,  // get_const(index) function pointer
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__get_function__SetParameters_Request__parameters,  // get(index) function pointer
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__fetch_function__SetParameters_Request__parameters,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__assign_function__SetParameters_Request__parameters,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__resize_function__SetParameters_Request__parameters  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetParameters_Request",  // message name
  1,  // number of fields
  sizeof(rcl_interfaces__srv__SetParameters_Request),
  rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_member_array,  // message members
  rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters_Request)() {
  rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, Parameter)();
  if (!rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetParameters_Request__rosidl_typesupport_introspection_c__SetParameters_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters__functions.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters__struct.h"


// Include directives for member types
// Member `results`
#include "rcl_interfaces/msg/set_parameters_result.h"
// Member `results`
#include "rcl_interfaces/msg/detail/set_parameters_result__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetParameters_Response__init(message_memory);
}

void rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetParameters_Response__fini(message_memory);
}

size_t rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__size_function__SetParameters_Response__results(
  const void * untyped_member)
{
  const rcl_interfaces__msg__SetParametersResult__Sequence * member =
    (const rcl_interfaces__msg__SetParametersResult__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__get_const_function__SetParameters_Response__results(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__msg__SetParametersResult__Sequence * member =
    (const rcl_interfaces__msg__SetParametersResult__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__get_function__SetParameters_Response__results(
  void * untyped_member, size_t index)
{
  rcl_interfaces__msg__SetParametersResult__Sequence * member =
    (rcl_interfaces__msg__SetParametersResult__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__fetch_function__SetParameters_Response__results(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__msg__SetParametersResult * item =
    ((const rcl_interfaces__msg__SetParametersResult *)
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__get_const_function__SetParameters_Response__results(untyped_member, index));
  rcl_interfaces__msg__SetParametersResult * value =
    (rcl_interfaces__msg__SetParametersResult *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__assign_function__SetParameters_Response__results(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__msg__SetParametersResult * item =
    ((rcl_interfaces__msg__SetParametersResult *)
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__get_function__SetParameters_Response__results(untyped_member, index));
  const rcl_interfaces__msg__SetParametersResult * value =
    (const rcl_interfaces__msg__SetParametersResult *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__resize_function__SetParameters_Response__results(
  void * untyped_member, size_t size)
{
  rcl_interfaces__msg__SetParametersResult__Sequence * member =
    (rcl_interfaces__msg__SetParametersResult__Sequence *)(untyped_member);
  rcl_interfaces__msg__SetParametersResult__Sequence__fini(member);
  return rcl_interfaces__msg__SetParametersResult__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_member_array[1] = {
  {
    "results",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParameters_Response, results),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__size_function__SetParameters_Response__results,  // size() function pointer
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__get_const_function__SetParameters_Response__results,  // get_const(index) function pointer
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__get_function__SetParameters_Response__results,  // get(index) function pointer
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__fetch_function__SetParameters_Response__results,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__assign_function__SetParameters_Response__results,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__resize_function__SetParameters_Response__results  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetParameters_Response",  // message name
  1,  // number of fields
  sizeof(rcl_interfaces__srv__SetParameters_Response),
  rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_member_array,  // message members
  rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters_Response)() {
  rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, SetParametersResult)();
  if (!rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetParameters_Response__rosidl_typesupport_introspection_c__SetParameters_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_members = {
  "rcl_interfaces__srv",  // service namespace
  "SetParameters",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_Request_message_type_support_handle,
  NULL  // response message
  // rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_Response_message_type_support_handle
};

static rosidl_service_type_support_t rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_type_support_handle = {
  0,
  &rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters)() {
  if (!rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParameters_Response)()->data;
  }

  return &rcl_interfaces__srv__detail__set_parameters__rosidl_typesupport_introspection_c__SetParameters_service_type_support_handle;
}
