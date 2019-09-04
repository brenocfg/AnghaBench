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
struct TYPE_3__ {scalar_t__ used; scalar_t__ buf; } ;
typedef  TYPE_1__ vbuf ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

void adns__vbuf_appendq(vbuf *vb, const byte *data, int len) {
  memcpy(vb->buf+vb->used,data, (size_t) len);
  vb->used+= len;
}