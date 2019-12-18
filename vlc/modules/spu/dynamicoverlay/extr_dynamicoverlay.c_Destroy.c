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
struct TYPE_8__ {struct TYPE_8__* psz_outputfile; struct TYPE_8__* psz_inputfile; int /*<<< orphan*/  lock; int /*<<< orphan*/  overlays; int /*<<< orphan*/  processed; int /*<<< orphan*/  pending; int /*<<< orphan*/  atomic; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustCallback ; 
 int /*<<< orphan*/  BufferDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QueueDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnregisterCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  do_ListDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Destroy( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    filter_sys_t *p_sys = p_filter->p_sys;

    BufferDestroy( &p_sys->input );
    BufferDestroy( &p_sys->output );
    QueueDestroy( &p_sys->atomic );
    QueueDestroy( &p_sys->pending );
    QueueDestroy( &p_sys->processed );
    do_ListDestroy( &p_sys->overlays );
    UnregisterCommand( p_filter );

    var_DelCallback( p_filter, "overlay-input", AdjustCallback, p_sys );
    var_DelCallback( p_filter, "overlay-output", AdjustCallback, p_sys );

    vlc_mutex_destroy( &p_sys->lock );
    free( p_sys->psz_inputfile );
    free( p_sys->psz_outputfile );
    free( p_sys );
}