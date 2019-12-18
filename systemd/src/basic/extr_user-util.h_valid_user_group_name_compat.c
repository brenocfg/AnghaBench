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
 int valid_user_group_name_full (char const*,int) ; 

__attribute__((used)) static inline bool valid_user_group_name_compat(const char *u) {
        return valid_user_group_name_full(u, false);
}