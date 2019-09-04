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
struct TYPE_4__ {scalar_t__ in_call; scalar_t__ object_state; } ;
typedef  TYPE_1__ DefaultHandler ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultHandler_Stop (TYPE_1__*) ; 
 scalar_t__ object_state_deferred_close ; 

__attribute__((used)) static inline void end_object_call(DefaultHandler *This)
{
    This->in_call--;
    if (This->in_call == 0 && This->object_state == object_state_deferred_close)
        DefaultHandler_Stop( This );
}