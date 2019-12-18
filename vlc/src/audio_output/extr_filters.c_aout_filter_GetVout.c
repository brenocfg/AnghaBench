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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_8__ {int /*<<< orphan*/ * fmt; int /*<<< orphan*/  clock; int /*<<< orphan*/ * vout; } ;
typedef  TYPE_2__ vout_configuration_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_7__ {int /*<<< orphan*/  sys; } ;
struct TYPE_9__ {TYPE_1__ owner; } ;
typedef  TYPE_3__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_AdjustColorSpace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vout_Create (int /*<<< orphan*/ ) ; 
 scalar_t__ vout_Request (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

vout_thread_t *aout_filter_GetVout(filter_t *filter, const video_format_t *fmt)
{
    vout_thread_t *vout = vout_Create(VLC_OBJECT(filter));
    if (unlikely(vout == NULL))
        return NULL;

    video_format_t adj_fmt = *fmt;
    vout_configuration_t cfg = {
        .vout = vout, .clock = filter->owner.sys, .fmt = &adj_fmt,
    };

    video_format_AdjustColorSpace(&adj_fmt);

    if (vout_Request(&cfg, NULL, NULL)) {
        vout_Close(vout);
        vout = NULL;
    }
    return vout;
}