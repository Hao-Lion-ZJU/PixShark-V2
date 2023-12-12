// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from underwater_robot_msgs:msg/Altimeter.idl
// generated code does not contain a copyright notice
#include "underwater_robot_msgs/msg/detail/altimeter__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
underwater_robot_msgs__msg__Altimeter__init(underwater_robot_msgs__msg__Altimeter * msg)
{
  if (!msg) {
    return false;
  }
  // height
  // correlation
  return true;
}

void
underwater_robot_msgs__msg__Altimeter__fini(underwater_robot_msgs__msg__Altimeter * msg)
{
  if (!msg) {
    return;
  }
  // height
  // correlation
}

bool
underwater_robot_msgs__msg__Altimeter__are_equal(const underwater_robot_msgs__msg__Altimeter * lhs, const underwater_robot_msgs__msg__Altimeter * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // correlation
  if (lhs->correlation != rhs->correlation) {
    return false;
  }
  return true;
}

bool
underwater_robot_msgs__msg__Altimeter__copy(
  const underwater_robot_msgs__msg__Altimeter * input,
  underwater_robot_msgs__msg__Altimeter * output)
{
  if (!input || !output) {
    return false;
  }
  // height
  output->height = input->height;
  // correlation
  output->correlation = input->correlation;
  return true;
}

underwater_robot_msgs__msg__Altimeter *
underwater_robot_msgs__msg__Altimeter__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  underwater_robot_msgs__msg__Altimeter * msg = (underwater_robot_msgs__msg__Altimeter *)allocator.allocate(sizeof(underwater_robot_msgs__msg__Altimeter), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(underwater_robot_msgs__msg__Altimeter));
  bool success = underwater_robot_msgs__msg__Altimeter__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
underwater_robot_msgs__msg__Altimeter__destroy(underwater_robot_msgs__msg__Altimeter * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    underwater_robot_msgs__msg__Altimeter__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
underwater_robot_msgs__msg__Altimeter__Sequence__init(underwater_robot_msgs__msg__Altimeter__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  underwater_robot_msgs__msg__Altimeter * data = NULL;

  if (size) {
    data = (underwater_robot_msgs__msg__Altimeter *)allocator.zero_allocate(size, sizeof(underwater_robot_msgs__msg__Altimeter), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = underwater_robot_msgs__msg__Altimeter__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        underwater_robot_msgs__msg__Altimeter__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
underwater_robot_msgs__msg__Altimeter__Sequence__fini(underwater_robot_msgs__msg__Altimeter__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      underwater_robot_msgs__msg__Altimeter__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

underwater_robot_msgs__msg__Altimeter__Sequence *
underwater_robot_msgs__msg__Altimeter__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  underwater_robot_msgs__msg__Altimeter__Sequence * array = (underwater_robot_msgs__msg__Altimeter__Sequence *)allocator.allocate(sizeof(underwater_robot_msgs__msg__Altimeter__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = underwater_robot_msgs__msg__Altimeter__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
underwater_robot_msgs__msg__Altimeter__Sequence__destroy(underwater_robot_msgs__msg__Altimeter__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    underwater_robot_msgs__msg__Altimeter__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
underwater_robot_msgs__msg__Altimeter__Sequence__are_equal(const underwater_robot_msgs__msg__Altimeter__Sequence * lhs, const underwater_robot_msgs__msg__Altimeter__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!underwater_robot_msgs__msg__Altimeter__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
underwater_robot_msgs__msg__Altimeter__Sequence__copy(
  const underwater_robot_msgs__msg__Altimeter__Sequence * input,
  underwater_robot_msgs__msg__Altimeter__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(underwater_robot_msgs__msg__Altimeter);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    underwater_robot_msgs__msg__Altimeter * data =
      (underwater_robot_msgs__msg__Altimeter *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!underwater_robot_msgs__msg__Altimeter__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          underwater_robot_msgs__msg__Altimeter__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!underwater_robot_msgs__msg__Altimeter__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
