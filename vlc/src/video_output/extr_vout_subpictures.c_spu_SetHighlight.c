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
typedef  int /*<<< orphan*/  vlc_spu_highlight_t ;
struct TYPE_6__ {TYPE_1__* p; } ;
typedef  TYPE_2__ spu_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateSPU (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_SetHighlight(spu_t *spu, const vlc_spu_highlight_t *hl)
{
    vlc_mutex_lock(&spu->p->lock);
    UpdateSPU(spu, hl);
    vlc_mutex_unlock(&spu->p->lock);
}