#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int avail; void* buf; } ;
typedef  TYPE_1__ vbuf ;

/* Variables and functions */
 void* realloc (void*,size_t) ; 

int adns__vbuf_ensure(vbuf *vb, int want) {
  void *nb;

  if (vb->avail >= want) return 1;
  nb= realloc(vb->buf, (size_t) want); if (!nb) return 0;
  vb->buf= nb;
  vb->avail= want;
  return 1;
}