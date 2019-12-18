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
typedef  int /*<<< orphan*/  opj_pi_iterator_t ;

/* Variables and functions */

__attribute__((used)) static void opj_pi_emit_error(opj_pi_iterator_t * pi, const char* msg)
{
    (void)pi;
    (void)msg;
}