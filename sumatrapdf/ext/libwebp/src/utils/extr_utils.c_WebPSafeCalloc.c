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
typedef  size_t uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddMem (void*,size_t) ; 
 int /*<<< orphan*/  CheckSizeArgumentsOverflow (size_t,size_t) ; 
 int /*<<< orphan*/  Increment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  num_calloc_calls ; 

void* WebPSafeCalloc(uint64_t nmemb, size_t size) {
  void* ptr;
  Increment(&num_calloc_calls);
  if (!CheckSizeArgumentsOverflow(nmemb, size)) return NULL;
  assert(nmemb * size > 0);
  ptr = calloc((size_t)nmemb, size);
  AddMem(ptr, (size_t)(nmemb * size));
  return ptr;
}