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
 void* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 size_t ROUND_SIZE (size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 

void* realloc(void* _ptr, size_t _size)
{
   size_t nSize;

   if (_ptr == NULL)
      return malloc(_size);

   if (_size == 0)
   {
   	   free(_ptr);
       return NULL;
   }

   nSize = ROUND_SIZE(_size);

   /* check for integer overflow */
   if (nSize<_size)
       return NULL;

   return HeapReAlloc(GetProcessHeap(), 0, _ptr, nSize);
}