// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from underwater_robot_msgs:msg/CabinInfo.idl
// generated code does not contain a copyright notice
#include "underwater_robot_msgs/msg/detail/cabin_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
underwater_robot_msgs__msg__CabinInfo__init(underwater_robot_msgs__msg__CabinInfo * msg)
{
  if (!msg) {
    return false;
  }
  // temperature
  // humidity
  // water_level
  // cpu_temperature
  return true;
}

void
underwater_robot_msgs__msg__CabinInfo__fini(underwater_robot_msgs__msg__CabinInfo * msg)
{
  if (!msg) {
    return;
  }
  // temperature
  // humidity
  // water_level
  // cpu_temperature
}

bool
underwater_robot_msgs__msg__CabinInfo__are_equal(const underwater_robot_msgs__msg__CabinInfo * lhs, const underwater_robot_msgs__msg__CabinInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // temperature
  if (lhs->temperature != rhs->temperature) {
    return false;
  }
  // humidity
  if (lhs->humidity != rhs->humidity) {
    return false;
  }
  // water_level
  if (lhs->water_level != rhs->water_level) {
    return false;
  }
  // cpu_temperature
  if (lhs->cpu_temperature != rhs->cpu_temperature) {
    return false;
  }
  return true;
}

bool
underwater_robot_msgs__msg__CabinInfo__copy(
  const underwater_robot_msgs__msg__CabinInfo * input,
  underwater_robot_msgs__msg__CabinInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // temperature
  output->temperature = input->temperature;
  // humidity
  output->humidity = input->humidity;
  // water_level
  output->water_level = input->water_level;
  // cpu_temperature
  output->cpu_temperature = input->cpu_temperature;
  return true;
}

underwater_robot_msgs__msg__CabinInfo *
underwater_robot_msgs__msg__CabinInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  underwater_robot_msgs__msg__CabinInfo * msg = (underwater_robot_msgs__msg__CabinInfo *)allocator.allocate(sizeof(underwater_robot_msgs__msg__CabinInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(underwater_robot_msgs__msg__CabinInfo));
  bool success = underwater_robot_msgs__msg__CabinInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
underwater_robot_msgs__msg__CabinInfo__destroy(underwater_robot_msgs__msg__CabinInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    underwater_robot_msgs__msg__CabinInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
underwater_robot_msgs__msg__CabinInfo__Sequence__init(underwater_robot_msgs__msg__CabinInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  underwater_robot_msgs__msg__CabinInfo * data = NULL;

  if (size) {
    data = (underwater_robot_msgs__msg__CabinInfo *)allocator.zero_allocate(size, sizeof(underwater_robot_msgs__msg__CabinInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = underwater_robot_msgs__msg__CabinInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        underwater_robot_msgs__msg__CabinInfo__fini(&data[i - 1]);
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
underwater_robot_msgs__msg__CabinInfo__Sequence__fini(underwater_robot_msgs__msg__CabinInfo__Sequence * array)
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
      underwater_robot_msgs__msg__CabinInfo__fini(&array->data[i]);
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

underwater_robot_msgs__msg__CabinInfo__Sequence *
underwater_robot_msgs__msg__CabinInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  underwater_robot_msgs__msg__CabinInfo__Sequence * array = (underwater_robot_msgs__msg__CabinInfo__Sequence *)allocator.allocate(sizeof(underwater_robot_msgs__msg__CabinInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = underwater_robot_msgs__msg__CabinInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
underwater_robot_msgs__msg__CabinInfo__Sequence__destroy(underwater_robot_msgs__msg__CabinInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    underwater_robot_msgs__msg__CabinInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
underwater_robot_msgs__msg__CabinInfo__Sequence__are_equal(const underwater_robot_msgs__msg__CabinInfo__Sequence * lhs, const underwater_robot_msgs__msg__CabinInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!underwater_robot_msgs__msg__CabinInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
underwater_robot_msgs__msg__CabinInfo__Sequence__copy(
  const underwater_robot_msgs__msg__CabinInfo__Sequence * input,
  underwater_robot_msgs__msg__CabinInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(underwater_robot_msgs__msg__CabinInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    underwater_robot_msgs__msg__CabinInfo * data =
      (underwater_robot_msgs__msg__CabinInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!underwater_robot_msgs__msg__CabinInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          underwater_robot_msgs__msg__CabinInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!underwater_robot_msgs__msg__CabinInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
