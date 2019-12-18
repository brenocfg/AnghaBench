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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  BrightnessCallback ; 
 int /*<<< orphan*/  ContrastCallback ; 
 int /*<<< orphan*/  HueCallback ; 
 int /*<<< orphan*/  SaturationCallback ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    filter_sys_t *sys = filter->p_sys;

    var_DelCallback(filter, "hue", HueCallback, &sys->hue);
    var_DelCallback(filter, "saturation", SaturationCallback,
                    &sys->saturation);
    var_DelCallback(filter, "contrast", ContrastCallback, &sys->contrast);
    var_DelCallback(filter, "brightness", BrightnessCallback,
                    &sys->brightness);
    free(sys);
}