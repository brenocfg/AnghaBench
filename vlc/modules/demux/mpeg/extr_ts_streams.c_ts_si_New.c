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
struct TYPE_5__ {int i_version; int /*<<< orphan*/ * cdtpid; int /*<<< orphan*/ * tdtpid; int /*<<< orphan*/ * eitpid; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ts_si_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 

ts_si_t *ts_si_New( demux_t *p_demux )
{
    ts_si_t *si = malloc( sizeof( ts_si_t ) );
    if( !si )
        return NULL;

    if( !handle_Init( p_demux, &si->handle ) )
    {
        free( si );
        return NULL;
    }

    si->i_version  = -1;
    si->eitpid = NULL;
    si->tdtpid = NULL;
    si->cdtpid = NULL;

    return si;
}