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
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * first; } ;
typedef  TYPE_1__ picture_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  picture_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

picture_t *picture_fifo_Peek(picture_fifo_t *fifo)
{
    vlc_mutex_lock(&fifo->lock);
    picture_t *picture = fifo->first;
    if (picture)
        picture_Hold(picture);
    vlc_mutex_unlock(&fifo->lock);

    return picture;
}