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
struct TYPE_4__ {scalar_t__ cgroups; scalar_t__ rax; } ;
typedef  TYPE_1__ stream ;

/* Variables and functions */
 scalar_t__ lpFree ; 
 int /*<<< orphan*/  raxFreeWithCallback (scalar_t__,void (*) (void*)) ; 
 scalar_t__ streamFreeCG ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void freeStream(stream *s) {
    raxFreeWithCallback(s->rax,(void(*)(void*))lpFree);
    if (s->cgroups)
        raxFreeWithCallback(s->cgroups,(void(*)(void*))streamFreeCG);
    zfree(s);
}