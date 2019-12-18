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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_8__ {int /*<<< orphan*/  heap; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_FACTOR ; 
 int /*<<< orphan*/  CFG_MIN_ALPHA ; 
 int /*<<< orphan*/  CFG_MIN_START_STOP_INTERVAL ; 
 int /*<<< orphan*/  CFG_MIN_STOPS_INTERVAL ; 
 int /*<<< orphan*/  CFG_MIN_STOP_START_INTERVAL ; 
 int /*<<< orphan*/  CFG_MODE ; 
 int /*<<< orphan*/  CFG_OVERLAP ; 
 int /*<<< orphan*/  SubsdelayCallback ; 
 int /*<<< orphan*/  SubsdelayHeapDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  var_Destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SubsdelayDestroy( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *) p_this;
    filter_sys_t *p_sys = p_filter->p_sys;

    SubsdelayHeapDestroy( &p_sys->heap );

    /* destroy parameters */

    var_DelCallback( p_filter, CFG_MODE, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_MODE );

    var_DelCallback( p_filter, CFG_FACTOR, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_FACTOR );

    var_DelCallback( p_filter, CFG_OVERLAP, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_OVERLAP );

    var_DelCallback( p_filter, CFG_MIN_ALPHA, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_MIN_ALPHA );

    var_DelCallback( p_filter, CFG_MIN_STOPS_INTERVAL, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_MIN_STOPS_INTERVAL );

    var_DelCallback( p_filter, CFG_MIN_STOP_START_INTERVAL, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_MIN_STOP_START_INTERVAL );

    var_DelCallback( p_filter, CFG_MIN_START_STOP_INTERVAL, SubsdelayCallback, p_sys );
    var_Destroy( p_filter, CFG_MIN_START_STOP_INTERVAL );

    free( p_sys );
}