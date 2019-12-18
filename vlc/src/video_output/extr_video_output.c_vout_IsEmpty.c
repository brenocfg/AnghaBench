#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_4__ {int /*<<< orphan*/  decoder_fifo; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_fifo_Peek (int /*<<< orphan*/ ) ; 

bool vout_IsEmpty(vout_thread_t *vout)
{
    assert(!vout->p->dummy);
    if (!vout->p->decoder_fifo)
        return true;

    picture_t *picture = picture_fifo_Peek(vout->p->decoder_fifo);
    if (picture)
        picture_Release(picture);

    return !picture;
}