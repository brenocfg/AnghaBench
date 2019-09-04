#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_6__ {int /*<<< orphan*/  parsed; int /*<<< orphan*/  nsscript; } ;
typedef  int /*<<< orphan*/  ScriptHost ;
typedef  scalar_t__ PRUnichar ;
typedef  TYPE_1__ HTMLScriptElement ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READYSTATE_COMPLETE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__ const*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,scalar_t__ const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLScriptElement_GetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLScriptElement_GetSrc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_extern_script (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  parse_inline_script (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_script_elem_readystate (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_script_elem(ScriptHost *script_host, HTMLScriptElement *script_elem)
{
    nsAString src_str, event_str;
    const PRUnichar *src;
    nsresult nsres;

    nsAString_Init(&event_str, NULL);
    nsres = nsIDOMHTMLScriptElement_GetEvent(script_elem->nsscript, &event_str);
    if(NS_SUCCEEDED(nsres)) {
        const PRUnichar *event;

        nsAString_GetData(&event_str, &event);
        if(*event) {
            TRACE("deferring event %s script evaluation\n", debugstr_w(event));
            nsAString_Finish(&event_str);
            return;
        }
    }else {
        ERR("GetEvent failed: %08x\n", nsres);
    }
    nsAString_Finish(&event_str);

    nsAString_Init(&src_str, NULL);
    nsres = nsIDOMHTMLScriptElement_GetSrc(script_elem->nsscript, &src_str);
    nsAString_GetData(&src_str, &src);

    if(NS_FAILED(nsres)) {
        ERR("GetSrc failed: %08x\n", nsres);
    }else if(*src) {
        script_elem->parsed = TRUE;
        parse_extern_script(script_host, script_elem, src);
    }else {
        parse_inline_script(script_host, script_elem);
    }

    nsAString_Finish(&src_str);

    set_script_elem_readystate(script_elem, READYSTATE_COMPLETE);
}