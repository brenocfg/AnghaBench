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
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_procedure_list; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_j2k_exec (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_setup_end_compress (TYPE_1__*,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_j2k_end_compress(opj_j2k_t *p_j2k,
                              opj_stream_private_t *p_stream,
                              opj_event_mgr_t * p_manager)
{
    /* customization of the encoding */
    if (! opj_j2k_setup_end_compress(p_j2k, p_manager)) {
        return OPJ_FALSE;
    }

    if (! opj_j2k_exec(p_j2k, p_j2k->m_procedure_list, p_stream, p_manager)) {
        return OPJ_FALSE;
    }

    return OPJ_TRUE;
}