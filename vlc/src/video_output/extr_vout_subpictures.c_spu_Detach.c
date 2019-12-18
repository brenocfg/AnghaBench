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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ spu_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * input; } ;

/* Variables and functions */
 int /*<<< orphan*/  spu_PrerenderPause (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_Detach(spu_t *spu)
{
    vlc_mutex_lock(&spu->p->lock);
    spu_PrerenderPause(spu->p);
    spu->p->input = NULL;
    vlc_mutex_unlock(&spu->p->lock);
}