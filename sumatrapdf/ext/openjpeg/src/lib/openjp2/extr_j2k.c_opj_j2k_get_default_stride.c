#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcp_t ;
typedef  int /*<<< orphan*/  OPJ_FLOAT32 ;

/* Variables and functions */

__attribute__((used)) static OPJ_FLOAT32 opj_j2k_get_default_stride(opj_tcp_t * p_tcp)
{
    (void)p_tcp;
    return 0;
}