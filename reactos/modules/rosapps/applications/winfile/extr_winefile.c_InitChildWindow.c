#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  filter_flags; int /*<<< orphan*/ * filter_pattern; int /*<<< orphan*/  right; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ ChildWnd ;

/* Variables and functions */
 int /*<<< orphan*/  IDW_HEADER_LEFT ; 
 int /*<<< orphan*/  IDW_HEADER_RIGHT ; 
 int /*<<< orphan*/  IDW_TREE_LEFT ; 
 int /*<<< orphan*/  IDW_TREE_RIGHT ; 
 int /*<<< orphan*/  TF_ALL ; 
 int /*<<< orphan*/  create_tree_window (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void InitChildWindow(ChildWnd* child)
{
	create_tree_window(child->hwnd, &child->left, IDW_TREE_LEFT, IDW_HEADER_LEFT, NULL, TF_ALL);
	create_tree_window(child->hwnd, &child->right, IDW_TREE_RIGHT, IDW_HEADER_RIGHT, child->filter_pattern, child->filter_flags);
}