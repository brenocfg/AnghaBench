#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* p; } ;
typedef  TYPE_5__ vout_thread_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_12__ {int /*<<< orphan*/  video; } ;
struct TYPE_9__ {TYPE_5__* sys; } ;
struct TYPE_14__ {TYPE_4__ fmt_out; TYPE_1__ owner; } ;
typedef  TYPE_6__ filter_t ;
struct TYPE_10__ {int /*<<< orphan*/  chain_interactive; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {TYPE_2__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/ * VoutVideoFilterInteractiveNewPicture (TYPE_6__*) ; 
 scalar_t__ filter_chain_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * picture_NewFromFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *VoutVideoFilterStaticNewPicture(filter_t *filter)
{
    vout_thread_t *vout = filter->owner.sys;

    vlc_mutex_assert(&vout->p->filter.lock);
    if (filter_chain_IsEmpty(vout->p->filter.chain_interactive))
        // we may be using the last filter of both chains, so we get the picture
        // from the display module pool, just like for the last interactive filter.
        return VoutVideoFilterInteractiveNewPicture(filter);

    return picture_NewFromFormat(&filter->fmt_out.video);
}