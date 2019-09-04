#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t ROUND_SIZE (size_t) ; 

void* malloc(size_t _size)
{
   size_t nSize = ROUND_SIZE(_size);

   if (nSize<_size)
       return NULL;

   return HeapAlloc(GetProcessHeap(), 0, nSize);
}