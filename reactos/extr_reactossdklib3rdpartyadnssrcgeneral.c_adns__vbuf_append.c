#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int used; int avail; void* buf; } ;
typedef  TYPE_1__ vbuf ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  adns__vbuf_appendq (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 void* realloc (void*,size_t) ; 

int adns__vbuf_append(vbuf *vb, const byte *data, int len) {
  int newlen;
  void *nb;

  newlen= vb->used+len;
  if (vb->avail < newlen) {
    if (newlen<20) newlen= 20;
    newlen <<= 1;
    nb= realloc(vb->buf,(size_t) newlen);
    if (!nb) { newlen= vb->used+len; nb= realloc(vb->buf, (size_t) newlen); }
    if (!nb) return 0;
    vb->buf= nb;
    vb->avail= newlen;
  }
  adns__vbuf_appendq(vb,data,len);
  return 1;
}