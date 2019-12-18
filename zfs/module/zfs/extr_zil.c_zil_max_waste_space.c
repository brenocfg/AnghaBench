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
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int zil_max_log_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint64_t
zil_max_waste_space(zilog_t *zilog)
{
	return (zil_max_log_data(zilog) / 8);
}