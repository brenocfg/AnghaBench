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
 void* lj_alloc_free (void*,void*) ; 
 void* lj_alloc_malloc (void*,size_t) ; 
 void* lj_alloc_realloc (void*,void*,size_t) ; 

void *lj_alloc_f(void *msp, void *ptr, size_t osize, size_t nsize)
{
  (void)osize;
  if (nsize == 0) {
    return lj_alloc_free(msp, ptr);
  } else if (ptr == NULL) {
    return lj_alloc_malloc(msp, nsize);
  } else {
    return lj_alloc_realloc(msp, ptr, nsize);
  }
}