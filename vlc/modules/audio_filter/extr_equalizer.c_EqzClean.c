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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {int /*<<< orphan*/  f_amp; int /*<<< orphan*/  f_gamma; int /*<<< orphan*/  f_beta; int /*<<< orphan*/  f_alpha; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  BandsCallback ; 
 int /*<<< orphan*/  PreampCallback ; 
 int /*<<< orphan*/  PresetCallback ; 
 int /*<<< orphan*/  TwoPassCallback ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * vlc_object_parent (TYPE_1__*) ; 

__attribute__((used)) static void EqzClean( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    vlc_object_t *p_aout = vlc_object_parent(p_filter);

    var_DelCallback( p_aout, "equalizer-bands", BandsCallback, p_sys );
    var_DelCallback( p_aout, "equalizer-preset", PresetCallback, p_sys );
    var_DelCallback( p_aout, "equalizer-preamp", PreampCallback, p_sys );
    var_DelCallback( p_aout, "equalizer-2pass", TwoPassCallback, p_sys );

    free( p_sys->f_alpha );
    free( p_sys->f_beta );
    free( p_sys->f_gamma );

    free( p_sys->f_amp );
}