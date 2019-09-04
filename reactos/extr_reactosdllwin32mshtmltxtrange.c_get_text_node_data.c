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
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  PRUnichar ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  IID_nsIDOMText ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ nsIDOMText_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMText_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_text_node_data(nsIDOMNode *node, nsAString *nsstr, const PRUnichar **str)
{
    nsIDOMText *nstext;
    nsresult nsres;

    nsres = nsIDOMNode_QueryInterface(node, &IID_nsIDOMText, (void**)&nstext);
    assert(nsres == NS_OK);

    nsAString_Init(nsstr, NULL);
    nsres = nsIDOMText_GetData(nstext, nsstr);
    nsIDOMText_Release(nstext);
    if(NS_FAILED(nsres))
        ERR("GetData failed: %08x\n", nsres);

    nsAString_GetData(nsstr, str);
}