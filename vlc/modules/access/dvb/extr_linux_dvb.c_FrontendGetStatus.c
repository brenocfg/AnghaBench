#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_last_status; } ;
typedef  TYPE_1__ frontend_t ;
struct TYPE_7__ {int b_has_signal; int b_has_carrier; int b_has_lock; } ;
typedef  TYPE_2__ frontend_status_t ;
struct TYPE_8__ {TYPE_1__* p_frontend; } ;
typedef  TYPE_3__ dvb_sys_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 

void FrontendGetStatus( dvb_sys_t *p_sys, frontend_status_t *p_status )
{
    frontend_t * p_frontend = p_sys->p_frontend;

    p_status->b_has_signal = (p_frontend->i_last_status & FE_HAS_SIGNAL) != 0;
    p_status->b_has_carrier = (p_frontend->i_last_status & FE_HAS_CARRIER) != 0;
    p_status->b_has_lock = (p_frontend->i_last_status & FE_HAS_LOCK) != 0;
}