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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PRUnichar ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_GetAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

nsresult get_elem_attr_value(nsIDOMHTMLElement *nselem, const WCHAR *name, nsAString *val_str, const PRUnichar **val)
{
    nsAString name_str;
    nsresult nsres;

    nsAString_InitDepend(&name_str, name);
    nsAString_Init(val_str, NULL);
    nsres = nsIDOMHTMLElement_GetAttribute(nselem, &name_str, val_str);
    nsAString_Finish(&name_str);
    if(NS_FAILED(nsres)) {
        ERR("GetAttribute(%s) failed: %08x\n", debugstr_w(name), nsres);
        nsAString_Finish(val_str);
        return nsres;
    }

    nsAString_GetData(val_str, val);
    return NS_OK;
}