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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__zpl_xattr_trusted_list(struct inode *ip, char *list, size_t list_size,
    const char *name, size_t name_len)
{
	return (capable(CAP_SYS_ADMIN));
}