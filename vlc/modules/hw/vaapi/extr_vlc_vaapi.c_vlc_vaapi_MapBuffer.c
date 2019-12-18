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
typedef  int /*<<< orphan*/  VADisplay ;
typedef  int /*<<< orphan*/  VABufferID ;

/* Variables and functions */
 int /*<<< orphan*/  VA_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vaMapBuffer ; 

int
vlc_vaapi_MapBuffer(vlc_object_t *o, VADisplay dpy,
                    VABufferID buf_id, void **p_buf)
{
    VA_CALL(o, vaMapBuffer, dpy, buf_id, p_buf);
    return VLC_SUCCESS;
error: return VLC_EGENERIC;
}