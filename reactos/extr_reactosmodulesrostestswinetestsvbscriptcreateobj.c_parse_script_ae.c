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
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 

__attribute__((used)) static HRESULT parse_script_ae(IActiveScriptParse *parser, const char *script)
{
    BSTR str;
    HRESULT hres;

    str = a2bstr(script);
    hres = IActiveScriptParse_ParseScriptText(parser, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    SysFreeString(str);

    return hres;
}