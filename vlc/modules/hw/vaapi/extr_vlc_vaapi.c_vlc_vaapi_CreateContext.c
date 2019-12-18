#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  VASurfaceID ;
typedef  int /*<<< orphan*/  VADisplay ;
typedef  int /*<<< orphan*/  VAContextID ;
typedef  int /*<<< orphan*/  VAConfigID ;

/* Variables and functions */
 int /*<<< orphan*/  VA_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VA_INVALID_ID ; 
 int /*<<< orphan*/  vaCreateContext ; 

VAContextID
vlc_vaapi_CreateContext(vlc_object_t *o, VADisplay dpy, VAConfigID conf,
                        int pic_w, int pic_h, int flag,
                        VASurfaceID *render_targets, int num_render_targets)
{
    VAContextID ctx;
    VA_CALL(o, vaCreateContext, dpy, conf, pic_w, pic_h, flag,
            render_targets, num_render_targets, &ctx);
    return ctx;
error: return VA_INVALID_ID;
}