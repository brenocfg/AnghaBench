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
struct TYPE_5__ {struct TYPE_5__* p_next; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_6__ {TYPE_1__** last_ptr; } ;
typedef  TYPE_2__ picture_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void PictureFifoPush(picture_fifo_t *fifo, picture_t *picture)
{
    assert(!picture->p_next);
    *fifo->last_ptr = picture;
    fifo->last_ptr  = &picture->p_next;
}