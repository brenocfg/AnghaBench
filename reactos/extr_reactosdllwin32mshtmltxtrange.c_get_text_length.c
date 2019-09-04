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
typedef  int /*<<< orphan*/  nsIDOMText ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  IID_nsIDOMText ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ nsIDOMText_GetLength (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMText_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT32 get_text_length(nsIDOMNode *node)
{
    nsIDOMText *nstext;
    UINT32 ret;
    nsresult nsres;

    nsres = nsIDOMNode_QueryInterface(node, &IID_nsIDOMText, (void**)&nstext);
    assert(nsres == NS_OK);

    nsres = nsIDOMText_GetLength(nstext, &ret);
    nsIDOMText_Release(nstext);
    assert(nsres == NS_OK);

    return ret;
}