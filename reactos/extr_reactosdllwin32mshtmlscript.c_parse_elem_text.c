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
typedef  int /*<<< orphan*/  excepinfo ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  parse; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HTMLScriptElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  READYSTATE_INTERACTIVE ; 
 int SCRIPTTEXT_HOSTMANAGESSOURCE ; 
 int SCRIPTTEXT_ISVISIBLE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  script_endW ; 
 int /*<<< orphan*/  set_script_elem_readystate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowW ; 

__attribute__((used)) static void parse_elem_text(ScriptHost *script_host, HTMLScriptElement *script_elem, LPCWSTR text)
{
    EXCEPINFO excepinfo;
    VARIANT var;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(text));

    set_script_elem_readystate(script_elem, READYSTATE_INTERACTIVE);

    VariantInit(&var);
    memset(&excepinfo, 0, sizeof(excepinfo));
    TRACE(">>>\n");
    hres = IActiveScriptParse_ParseScriptText(script_host->parse, text, windowW, NULL, script_endW,
                                              0, 0, SCRIPTTEXT_ISVISIBLE|SCRIPTTEXT_HOSTMANAGESSOURCE,
                                              &var, &excepinfo);
    if(SUCCEEDED(hres))
        TRACE("<<<\n");
    else
        WARN("<<< %08x\n", hres);

}