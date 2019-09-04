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
struct ext4_xattr_ref {int /*<<< orphan*/ * iter_arg; } ;
struct ext4_xattr_item {int name_len; int data_size; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int EXT4_XATTR_ITERATE_CONT ; 

__attribute__((used)) static int Ext2IterateAllEa(struct ext4_xattr_ref *xattr_ref, struct ext4_xattr_item *item, BOOL is_last)
{
    PULONG EaSize = xattr_ref->iter_arg;
    ULONG EaEntrySize = 4 + 1 + 1 + 2 + item->name_len + 1 + item->data_size;

    *EaSize += EaEntrySize - 4;
    return EXT4_XATTR_ITERATE_CONT;
}