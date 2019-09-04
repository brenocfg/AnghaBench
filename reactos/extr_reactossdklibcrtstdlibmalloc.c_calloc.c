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
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t ROUND_SIZE (size_t) ; 

void* calloc(size_t _nmemb, size_t _size)
{
   size_t nSize = _nmemb * _size;
   size_t cSize = ROUND_SIZE(nSize);

   if ( (_nmemb > ((size_t)-1 / _size))  || (cSize<nSize))
      return NULL;

   return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cSize );
}