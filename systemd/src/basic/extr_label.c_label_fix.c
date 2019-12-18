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
typedef  int /*<<< orphan*/  LabelFixFlags ;

/* Variables and functions */
 int mac_selinux_fix (char const*,int /*<<< orphan*/ ) ; 
 int mac_smack_fix (char const*,int /*<<< orphan*/ ) ; 

int label_fix(const char *path, LabelFixFlags flags) {
        int r, q;

        r = mac_selinux_fix(path, flags);
        q = mac_smack_fix(path, flags);

        if (r < 0)
                return r;
        if (q < 0)
                return q;

        return 0;
}