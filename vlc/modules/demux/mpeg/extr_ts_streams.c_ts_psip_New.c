#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_version; int /*<<< orphan*/  p_ctx; int /*<<< orphan*/ * p_eas_es; int /*<<< orphan*/  eit; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ts_psip_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  ts_psip_Del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ts_psip_context_New () ; 

ts_psip_t *ts_psip_New( demux_t *p_demux )
{
    ts_psip_t *psip = malloc( sizeof( ts_psip_t ) );
    if( !psip )
        return NULL;

    if( !handle_Init( p_demux, &psip->handle ) )
    {
        free( psip );
        return NULL;
    }

    ARRAY_INIT( psip->eit );
    psip->i_version  = -1;
    psip->p_eas_es = NULL;
    psip->p_ctx = ts_psip_context_New();
    if( !psip->p_ctx )
    {
        ts_psip_Del( p_demux, psip );
        psip = NULL;
    }

    return psip;
}