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

/* Variables and functions */
 scalar_t__ init_system_thp_mode ; 
 scalar_t__ metadata_thp_enabled () ; 
 scalar_t__ thp_mode_default ; 

__attribute__((used)) static inline bool
metadata_thp_madvise(void) {
	return (metadata_thp_enabled() &&
	    (init_system_thp_mode == thp_mode_default));
}