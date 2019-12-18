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
struct TYPE_7__ {TYPE_1__* p; } ;
typedef  TYPE_2__ spu_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  textlock; scalar_t__ text; int /*<<< orphan*/ * input; } ;

/* Variables and functions */
 int /*<<< orphan*/  FilterRelease (scalar_t__) ; 
 scalar_t__ SpuRenderCreateAndLoadText (TYPE_2__*) ; 
 int /*<<< orphan*/  UpdateSPU (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_Attach(spu_t *spu, input_thread_t *input)
{
    vlc_mutex_lock(&spu->p->lock);
    if (spu->p->input != input) {
        UpdateSPU(spu, NULL);

        spu->p->input = input;

        vlc_mutex_lock(&spu->p->textlock);
        if (spu->p->text)
            FilterRelease(spu->p->text);
        spu->p->text = SpuRenderCreateAndLoadText(spu);
        vlc_mutex_unlock(&spu->p->textlock);
    }
    vlc_mutex_unlock(&spu->p->lock);
}