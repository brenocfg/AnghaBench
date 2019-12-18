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
struct TYPE_3__ {scalar_t__ m_data_size; int /*<<< orphan*/ * m_data; } ;
typedef  TYPE_1__ opj_tcp_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opj_j2k_tcp_data_destroy(opj_tcp_t *p_tcp)
{
    if (p_tcp->m_data) {
        opj_free(p_tcp->m_data);
        p_tcp->m_data = NULL;
        p_tcp->m_data_size = 0;
    }
}