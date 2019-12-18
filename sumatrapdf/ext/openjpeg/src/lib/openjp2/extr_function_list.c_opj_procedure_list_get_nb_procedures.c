#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  m_nb_procedures; } ;
typedef  TYPE_1__ opj_procedure_list_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;

/* Variables and functions */

OPJ_UINT32 opj_procedure_list_get_nb_procedures(opj_procedure_list_t *
        p_validation_list)
{
    return p_validation_list->m_nb_procedures;
}