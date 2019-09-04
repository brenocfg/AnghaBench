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
typedef  void byte ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 

void adns__isort(void *array, int nobjs, int sz, void *tempbuf,
		 int (*needswap)(void *context, const void *a, const void *b),
		 void *context) {
  byte *data= array;
  int i, place;

  for (i=0; i<nobjs; i++) {
    for (place= i;
	 place>0 && needswap(context, data + (place-1)*sz, data + i*sz);
	 place--);
    if (place != i) {
      memcpy(tempbuf, data + i*sz, (size_t) sz);
      memmove(data + (place+1)*sz, data + place*sz, (size_t) (i-place)*sz);
      memcpy(data + place*sz, tempbuf, (size_t) sz);
    }
  }
}