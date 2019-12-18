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
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  vector; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  const* p_processed; } ;
struct TYPE_5__ {TYPE_1__ prerender; } ;
typedef  TYPE_2__ spu_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_index_of (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__*) ; 

__attribute__((used)) static void spu_PrerenderSync(spu_private_t *sys, const subpicture_t *p_subpic)
{
    vlc_mutex_lock(&sys->prerender.lock);
    ssize_t i_idx;
    vlc_vector_index_of(&sys->prerender.vector, p_subpic, &i_idx);
    while(i_idx >= 0 || sys->prerender.p_processed == p_subpic)
    {
        vlc_cond_wait(&sys->prerender.output_cond, &sys->prerender.lock);
        vlc_vector_index_of(&sys->prerender.vector, p_subpic, &i_idx);
    }
    vlc_mutex_unlock(&sys->prerender.lock);
}