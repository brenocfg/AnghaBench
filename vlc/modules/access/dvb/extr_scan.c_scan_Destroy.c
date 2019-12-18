#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t i_multiplex; int /*<<< orphan*/  p_scanlist; struct TYPE_5__* pp_multiplex; int /*<<< orphan*/  parameter; int /*<<< orphan*/ * p_dialog_id; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_1__ scan_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  scan_list_entries_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_multiplex_Delete (TYPE_1__) ; 
 int /*<<< orphan*/  scan_parameter_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void scan_Destroy( scan_t *p_scan )
{
    if( !p_scan )
        return;
    if( p_scan->p_dialog_id != NULL )
        vlc_dialog_release( p_scan->p_obj, p_scan->p_dialog_id );

    scan_parameter_Clean( &p_scan->parameter );

    for( size_t i = 0; i < p_scan->i_multiplex; i++ )
        scan_multiplex_Delete( p_scan->pp_multiplex[i] );
    free( p_scan->pp_multiplex );

    scan_list_entries_release( p_scan->p_scanlist );

    free( p_scan );
}