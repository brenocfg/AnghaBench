#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scan_tuner_config_t ;
struct TYPE_10__ {int /*<<< orphan*/  type; int /*<<< orphan*/  b_use_nit; } ;
struct TYPE_12__ {TYPE_2__ parameter; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_4__ scan_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pp_sdt; int /*<<< orphan*/ * pp_nit; scalar_t__ i_sdt; scalar_t__ i_nit; } ;
struct TYPE_9__ {int /*<<< orphan*/ * p_nit; int /*<<< orphan*/ * p_sdt; int /*<<< orphan*/ * p_pat; } ;
struct TYPE_13__ {int i_snr; int i_nit_pid; int /*<<< orphan*/ * p_nithandle; int /*<<< orphan*/ * p_sdthandle; int /*<<< orphan*/ * p_pathandle; TYPE_3__ others; int /*<<< orphan*/  type; int /*<<< orphan*/  b_use_nit; TYPE_1__ local; int /*<<< orphan*/  cfg; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_5__ scan_session_t ;

/* Variables and functions */
 TYPE_5__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static scan_session_t *scan_session_New( scan_t *p_scan, const scan_tuner_config_t *p_cfg )
{
    scan_session_t *p_session = malloc( sizeof( *p_session ) );
    if( unlikely(p_session == NULL) )
        return NULL;
    p_session->p_obj = p_scan->p_obj;
    p_session->cfg = *p_cfg;
    p_session->i_snr = -1;
    p_session->local.p_pat = NULL;
    p_session->local.p_sdt = NULL;
    p_session->local.p_nit = NULL;
    p_session->i_nit_pid = -1;
    p_session->b_use_nit = p_scan->parameter.b_use_nit;
    p_session->type = p_scan->parameter.type;
    p_session->others.i_nit = 0;
    p_session->others.i_sdt = 0;
    p_session->others.pp_nit = NULL;
    p_session->others.pp_sdt = NULL;
    p_session->p_pathandle = NULL;
    p_session->p_sdthandle = NULL;
    p_session->p_nithandle = NULL;
    return p_session;;
}