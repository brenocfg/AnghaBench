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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  CopyFlags ;

/* Variables and functions */
 int copy_file_full (char const*,char const*,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int copy_file(const char *from, const char *to, int open_flags, mode_t mode, unsigned chattr_flags, unsigned chattr_mask, CopyFlags copy_flags) {
        return copy_file_full(from, to, open_flags, mode, chattr_flags, chattr_mask, copy_flags, NULL, NULL);
}