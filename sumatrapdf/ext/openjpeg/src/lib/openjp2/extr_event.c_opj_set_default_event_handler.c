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
struct TYPE_3__ {int m_error_data; int m_warning_data; int m_info_data; void* warning_handler; void* info_handler; void* error_handler; } ;
typedef  TYPE_1__ opj_event_mgr_t ;

/* Variables and functions */
 void* opj_default_callback ; 

void opj_set_default_event_handler(opj_event_mgr_t * p_manager)
{
    p_manager->m_error_data = 00;
    p_manager->m_warning_data = 00;
    p_manager->m_info_data = 00;
    p_manager->error_handler = opj_default_callback;
    p_manager->info_handler = opj_default_callback;
    p_manager->warning_handler = opj_default_callback;
}