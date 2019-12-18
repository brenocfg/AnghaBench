#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_cfg; int /*<<< orphan*/  pf_sub_source; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_10__ {int i_inputfd; int i_outputfd; int b_updated; int b_atomic; void* psz_outputfile; void* psz_inputfile; int /*<<< orphan*/  lock; int /*<<< orphan*/  overlays; int /*<<< orphan*/  processed; int /*<<< orphan*/  pending; int /*<<< orphan*/  atomic; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustCallback ; 
 int /*<<< orphan*/  BufferInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  QueueInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterCommand (TYPE_1__*) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  config_ChainParse (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_ListInit (int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  ppsz_filter_options ; 
 int /*<<< orphan*/  var_AddCallback (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* var_CreateGetStringCommand (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Create( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    filter_sys_t *p_sys;

    /* Allocate structure */
    p_filter->p_sys = malloc( sizeof( filter_sys_t ) );
    if( p_filter->p_sys == NULL )
        return VLC_ENOMEM;
    p_sys = p_filter->p_sys;

    BufferInit( &p_sys->input );
    BufferInit( &p_sys->output );
    QueueInit( &p_sys->atomic );
    QueueInit( &p_sys->pending );
    QueueInit( &p_sys->processed );
    do_ListInit( &p_sys->overlays );

    p_sys->i_inputfd = -1;
    p_sys->i_outputfd = -1;
    p_sys->b_updated = true;
    p_sys->b_atomic = false;
    vlc_mutex_init( &p_sys->lock );

    p_filter->pf_sub_source = Filter;

    config_ChainParse( p_filter, "overlay-", ppsz_filter_options,
                       p_filter->p_cfg );

    p_sys->psz_inputfile = var_CreateGetStringCommand( p_filter,
                                                       "overlay-input" );
    p_sys->psz_outputfile = var_CreateGetStringCommand( p_filter,
                                                        "overlay-output" );

    var_AddCallback( p_filter, "overlay-input", AdjustCallback, p_sys );
    var_AddCallback( p_filter, "overlay-output", AdjustCallback, p_sys );

    RegisterCommand( p_filter );
    return VLC_SUCCESS;
}