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
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ vbuf ;

/* Variables and functions */
 int /*<<< orphan*/  adns__vbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void adns__vbuf_free(vbuf *vb) {
  free(vb->buf);
  adns__vbuf_init(vb);
}