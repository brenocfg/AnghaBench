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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  CopyFlags ;

/* Variables and functions */
 int copy_tree_at_full (int,char const*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int copy_tree_at(int fdf, const char *from, int fdt, const char *to, uid_t override_uid, gid_t override_gid, CopyFlags copy_flags) {
        return copy_tree_at_full(fdf, from, fdt, to, override_uid, override_gid, copy_flags, NULL, NULL, NULL);
}