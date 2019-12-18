#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p_next; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_7__ {int /*<<< orphan*/  control; int /*<<< orphan*/  decoder_fifo; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  picture_fifo_Push (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vout_control_Wake (int /*<<< orphan*/ *) ; 

void vout_PutPicture(vout_thread_t *vout, picture_t *picture)
{
    assert(!vout->p->dummy);
    picture->p_next = NULL;
    picture_fifo_Push(vout->p->decoder_fifo, picture);
    vout_control_Wake(&vout->p->control);
}