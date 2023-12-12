/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : common.cpp
 * @brief     : some common function
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-12-1       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */


#include "common.hpp"

void* operator new(size_t size) 				//重载全局operator new
{
	return pvPortMalloc(size);
}
void* operator new[](size_t size)				//重载全局operator new[]
{
	return pvPortMalloc(size);
}
void operator delete(void* phead) 		//重载全局operator delete
{
	vPortFree(phead);
}
void operator delete[](void* phead)	//重载全局operator delete[]
{
	vPortFree(phead);
}