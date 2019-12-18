#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_7__ {scalar_t__ format; } ;
typedef  TYPE_1__ audio_volume_t ;
struct TYPE_8__ {int /*<<< orphan*/ * module; TYPE_1__ object; } ;
typedef  TYPE_2__ aout_volume_t ;

/* Variables and functions */
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int aout_volume_SetFormat(aout_volume_t *vol, vlc_fourcc_t format)
{
    if (unlikely(vol == NULL))
        return -1;

    audio_volume_t *obj = &vol->object;
    if (vol->module != NULL)
    {
        if (obj->format == format)
        {
            msg_Dbg (obj, "retaining sample format");
            return 0;
        }
        msg_Dbg (obj, "changing sample format");
        module_unneed(obj, vol->module);
    }

    obj->format = format;
    vol->module = module_need(obj, "audio volume", NULL, false);
    if (vol->module == NULL)
        return -1;
    return 0;
}