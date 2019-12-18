#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int z_flags; } ;

/* Variables and functions */
 TYPE_1__* ITOZSB (struct inode*) ; 
 int ZSB_XATTR ; 

__attribute__((used)) static int
__zpl_xattr_user_list(struct inode *ip, char *list, size_t list_size,
    const char *name, size_t name_len)
{
	return (ITOZSB(ip)->z_flags & ZSB_XATTR);
}