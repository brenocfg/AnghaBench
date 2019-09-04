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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMNode_GetChildNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT32 get_child_count(nsIDOMNode *node)
{
    nsIDOMNodeList *node_list;
    UINT32 ret;
    nsresult nsres;

    nsres = nsIDOMNode_GetChildNodes(node, &node_list);
    assert(nsres == NS_OK);

    nsres = nsIDOMNodeList_GetLength(node_list, &ret);
    nsIDOMNodeList_Release(node_list);
    assert(nsres == NS_OK);

    return ret;
}