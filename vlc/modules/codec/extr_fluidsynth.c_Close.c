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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  synth; int /*<<< orphan*/  soundfont; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_fluid_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_fluid_synth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fluid_synth_sfunload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close (vlc_object_t *p_this)
{
    decoder_sys_t *p_sys = ((decoder_t *)p_this)->p_sys;

    fluid_synth_sfunload (p_sys->synth, p_sys->soundfont, 1);
    delete_fluid_synth (p_sys->synth);
    delete_fluid_settings (p_sys->settings);
    free (p_sys);
}