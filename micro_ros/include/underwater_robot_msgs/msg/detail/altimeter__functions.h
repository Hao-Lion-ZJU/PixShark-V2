// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from underwater_robot_msgs:msg/Altimeter.idl
// generated code does not contain a copyright notice

#ifndef UNDERWATER_ROBOT_MSGS__MSG__DETAIL__ALTIMETER__FUNCTIONS_H_
#define UNDERWATER_ROBOT_MSGS__MSG__DETAIL__ALTIMETER__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "underwater_robot_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "underwater_robot_msgs/msg/detail/altimeter__struct.h"

/// Initialize msg/Altimeter message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * underwater_robot_msgs__msg__Altimeter
 * )) before or use
 * underwater_robot_msgs__msg__Altimeter__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
bool
underwater_robot_msgs__msg__Altimeter__init(underwater_robot_msgs__msg__Altimeter * msg);

/// Finalize msg/Altimeter message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
void
underwater_robot_msgs__msg__Altimeter__fini(underwater_robot_msgs__msg__Altimeter * msg);

/// Create msg/Altimeter message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * underwater_robot_msgs__msg__Altimeter__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
underwater_robot_msgs__msg__Altimeter *
underwater_robot_msgs__msg__Altimeter__create();

/// Destroy msg/Altimeter message.
/**
 * It calls
 * underwater_robot_msgs__msg__Altimeter__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
void
underwater_robot_msgs__msg__Altimeter__destroy(underwater_robot_msgs__msg__Altimeter * msg);

/// Check for msg/Altimeter message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
bool
underwater_robot_msgs__msg__Altimeter__are_equal(const underwater_robot_msgs__msg__Altimeter * lhs, const underwater_robot_msgs__msg__Altimeter * rhs);

/// Copy a msg/Altimeter message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
bool
underwater_robot_msgs__msg__Altimeter__copy(
  const underwater_robot_msgs__msg__Altimeter * input,
  underwater_robot_msgs__msg__Altimeter * output);

/// Initialize array of msg/Altimeter messages.
/**
 * It allocates the memory for the number of elements and calls
 * underwater_robot_msgs__msg__Altimeter__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
bool
underwater_robot_msgs__msg__Altimeter__Sequence__init(underwater_robot_msgs__msg__Altimeter__Sequence * array, size_t size);

/// Finalize array of msg/Altimeter messages.
/**
 * It calls
 * underwater_robot_msgs__msg__Altimeter__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
void
underwater_robot_msgs__msg__Altimeter__Sequence__fini(underwater_robot_msgs__msg__Altimeter__Sequence * array);

/// Create array of msg/Altimeter messages.
/**
 * It allocates the memory for the array and calls
 * underwater_robot_msgs__msg__Altimeter__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
underwater_robot_msgs__msg__Altimeter__Sequence *
underwater_robot_msgs__msg__Altimeter__Sequence__create(size_t size);

/// Destroy array of msg/Altimeter messages.
/**
 * It calls
 * underwater_robot_msgs__msg__Altimeter__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
void
underwater_robot_msgs__msg__Altimeter__Sequence__destroy(underwater_robot_msgs__msg__Altimeter__Sequence * array);

/// Check for msg/Altimeter message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
bool
underwater_robot_msgs__msg__Altimeter__Sequence__are_equal(const underwater_robot_msgs__msg__Altimeter__Sequence * lhs, const underwater_robot_msgs__msg__Altimeter__Sequence * rhs);

/// Copy an array of msg/Altimeter messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_underwater_robot_msgs
bool
underwater_robot_msgs__msg__Altimeter__Sequence__copy(
  const underwater_robot_msgs__msg__Altimeter__Sequence * input,
  underwater_robot_msgs__msg__Altimeter__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UNDERWATER_ROBOT_MSGS__MSG__DETAIL__ALTIMETER__FUNCTIONS_H_
