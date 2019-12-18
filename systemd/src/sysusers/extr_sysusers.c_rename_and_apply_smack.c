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
 int /*<<< orphan*/  SMACK_ATTR_ACCESS ; 
 int /*<<< orphan*/  SMACK_FLOOR_LABEL ; 
 int errno ; 
 int mac_smack_apply (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rename (char const*,char const*) ; 

__attribute__((used)) static int rename_and_apply_smack(const char *temp_path, const char *dest_path) {
        int r = 0;
        if (rename(temp_path, dest_path) < 0)
                return -errno;

#ifdef SMACK_RUN_LABEL
        r = mac_smack_apply(dest_path, SMACK_ATTR_ACCESS, SMACK_FLOOR_LABEL);
        if (r < 0)
                return r;
#endif
        return r;
}