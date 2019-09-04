#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ LesserChild; struct TYPE_4__* IndexEntry; } ;
typedef  TYPE_1__* PB_TREE_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyBTreeNode (scalar_t__) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS ; 

VOID
DestroyBTreeKey(PB_TREE_KEY Key)
{
    if (Key->IndexEntry)
        ExFreePoolWithTag(Key->IndexEntry, TAG_NTFS);

    if (Key->LesserChild)
        DestroyBTreeNode(Key->LesserChild);

    ExFreePoolWithTag(Key, TAG_NTFS);
}