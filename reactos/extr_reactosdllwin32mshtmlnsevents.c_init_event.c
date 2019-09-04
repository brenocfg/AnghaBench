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
typedef  int /*<<< orphan*/  nsIDOMEventTarget ;
typedef  int /*<<< orphan*/  nsIDOMEventListener ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMEventTarget_AddEventListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_event(nsIDOMEventTarget *target, const PRUnichar *type,
        nsIDOMEventListener *listener, BOOL capture)
{
    nsAString type_str;
    nsresult nsres;

    nsAString_InitDepend(&type_str, type);
    nsres = nsIDOMEventTarget_AddEventListener(target, &type_str, listener, capture, FALSE, 1);
    nsAString_Finish(&type_str);
    if(NS_FAILED(nsres))
        ERR("AddEventTarget failed: %08x\n", nsres);

}