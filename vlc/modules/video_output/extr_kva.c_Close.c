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
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_5__ {int /*<<< orphan*/  ack_event; int /*<<< orphan*/  tid; int /*<<< orphan*/  hmq; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCWW_WAIT ; 
 int /*<<< orphan*/  DosCloseEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosWaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_QUIT ; 
 int /*<<< orphan*/  WinPostQueueMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close ( vlc_object_t *object )
{
    vout_display_t * vd = (vout_display_t *)object;
    vout_display_sys_t * sys = vd->sys;

    WinPostQueueMsg( sys->hmq, WM_QUIT, 0, 0 );

    DosWaitThread( &sys->tid, DCWW_WAIT );

    DosCloseEventSem( sys->ack_event );

    free( sys );
}