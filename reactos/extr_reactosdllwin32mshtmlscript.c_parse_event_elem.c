#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  window; } ;
struct TYPE_9__ {int /*<<< orphan*/  nsscript; scalar_t__ parsed; } ;
struct TYPE_8__ {int /*<<< orphan*/  parse_proc; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_2__ HTMLScriptElement ;
typedef  TYPE_3__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptParseProcedure2_ParseProcedureText (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int SCRIPTPROC_HOSTMANAGESSOURCE ; 
 int SCRIPTPROC_IMPLICIT_PARENTS ; 
 int SCRIPTPROC_IMPLICIT_THIS ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emptyW ; 
 TYPE_1__* get_elem_script_host (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLScriptElement_GetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLScriptElement_GetText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_event_str (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  script_endW ; 

__attribute__((used)) static IDispatch *parse_event_elem(HTMLDocumentNode *doc, HTMLScriptElement *script_elem, WCHAR **ret_event)
{
    ScriptHost *script_host;
    WCHAR *event = NULL;
    const WCHAR *args;
    nsAString nsstr;
    IDispatch *disp;
    nsresult nsres;
    HRESULT hres;

    if(script_elem->parsed)
        return NULL;

    script_host = get_elem_script_host(doc->window, script_elem);
    if(!script_host || !script_host->parse_proc)
        return NULL;

    nsAString_Init(&nsstr, NULL);
    nsres = nsIDOMHTMLScriptElement_GetEvent(script_elem->nsscript, &nsstr);
    if(NS_SUCCEEDED(nsres)) {
        const PRUnichar *event_val;

        nsAString_GetData(&nsstr, &event_val);
        event = heap_strdupW(event_val);
    }
    nsAString_Finish(&nsstr);
    if(!event)
        return NULL;

    if(!parse_event_str(event, &args)) {
        WARN("parsing %s failed\n", debugstr_w(event));
        heap_free(event);
        return NULL;
    }

    nsAString_Init(&nsstr, NULL);
    nsres = nsIDOMHTMLScriptElement_GetText(script_elem->nsscript, &nsstr);
    if(NS_SUCCEEDED(nsres)) {
        const PRUnichar *text;

        nsAString_GetData(&nsstr, &text);
        hres = IActiveScriptParseProcedure2_ParseProcedureText(script_host->parse_proc, text, args,
                emptyW, NULL, NULL, script_endW, 0, 0,
                SCRIPTPROC_HOSTMANAGESSOURCE|SCRIPTPROC_IMPLICIT_THIS|SCRIPTPROC_IMPLICIT_PARENTS, &disp);
        if(FAILED(hres))
            disp = NULL;
    }else {
        ERR("GetText failed: %08x\n", nsres);
        disp = NULL;
    }
    nsAString_Finish(&nsstr);
    if(!disp) {
        heap_free(event);
        return NULL;
    }

    *ret_event = event;
    return disp;
}