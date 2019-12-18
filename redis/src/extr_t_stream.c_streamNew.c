#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ seq; scalar_t__ ms; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cgroups; TYPE_1__ last_id; scalar_t__ length; int /*<<< orphan*/  rax; } ;
typedef  TYPE_2__ stream ;

/* Variables and functions */
 int /*<<< orphan*/  raxNew () ; 
 TYPE_2__* zmalloc (int) ; 

stream *streamNew(void) {
    stream *s = zmalloc(sizeof(*s));
    s->rax = raxNew();
    s->length = 0;
    s->last_id.ms = 0;
    s->last_id.seq = 0;
    s->cgroups = NULL; /* Created on demand to save memory when not used. */
    return s;
}