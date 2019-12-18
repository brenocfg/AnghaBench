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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EEXIST ; 
 int mkdir_errno_wrapper (char const*,int /*<<< orphan*/ ) ; 
 char* prefix_roota (char const*,char const*) ; 
 int userns_lchown (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int userns_mkdir(const char *root, const char *path, mode_t mode, uid_t uid, gid_t gid) {
        const char *q;
        int r;

        q = prefix_roota(root, path);
        r = mkdir_errno_wrapper(q, mode);
        if (r == -EEXIST)
                return 0;
        if (r < 0)
                return r;

        return userns_lchown(q, uid, gid);
}