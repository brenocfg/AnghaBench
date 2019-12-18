#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* m_procedures; } ;
typedef  TYPE_1__ opj_procedure_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 

void  opj_procedure_list_destroy(opj_procedure_list_t * p_list)
{
    if (! p_list) {
        return;
    }
    /* initialization */
    if (p_list->m_procedures) {
        opj_free(p_list->m_procedures);
    }
    opj_free(p_list);
}