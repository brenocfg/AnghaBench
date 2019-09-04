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
struct hierarchy_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ lParam; int /*<<< orphan*/ * hItem; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVGN_PARENT ; 
 int /*<<< orphan*/  TVIF_PARAM ; 
 int /*<<< orphan*/  TVM_GETITEMW ; 
 int /*<<< orphan*/  TVM_GETNEXTITEM ; 

__attribute__((used)) static struct hierarchy_data *get_hierarchy_data_from_tree_item(HWND tree,
 HTREEITEM hItem)
{
    struct hierarchy_data *data = NULL;
    HTREEITEM root = NULL;

    do {
        HTREEITEM parent = (HTREEITEM)SendMessageW(tree, TVM_GETNEXTITEM,
         TVGN_PARENT, (LPARAM)hItem);

        if (!parent)
            root = hItem;
        hItem = parent;
    } while (hItem);
    if (root)
    {
        TVITEMW item;

        item.mask = TVIF_PARAM;
        item.hItem = root;
        SendMessageW(tree, TVM_GETITEMW, 0, (LPARAM)&item);
        data = (struct hierarchy_data *)item.lParam;
    }
    return data;
}