#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_7__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 TYPE_2__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_FifoPut (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void VoutDisplayEventKey(vout_display_sys_t *sys, int key)
{
    block_t *event = block_Alloc(sizeof (key));
    if (likely(event != NULL)) {
        memcpy(event->p_buffer, &key, sizeof (key));
        block_FifoPut(sys->fifo, event);
    }
}