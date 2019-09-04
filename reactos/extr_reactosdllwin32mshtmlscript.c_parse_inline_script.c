#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_4__ {int /*<<< orphan*/  nsscript; } ;
typedef  int /*<<< orphan*/  ScriptHost ;
typedef  scalar_t__ PRUnichar ;
typedef  TYPE_1__ HTMLScriptElement ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,scalar_t__ const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLScriptElement_GetText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_elem_text (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__ const*) ; 

__attribute__((used)) static void parse_inline_script(ScriptHost *script_host, HTMLScriptElement *script_elem)
{
    const PRUnichar *text;
    nsAString text_str;
    nsresult nsres;

    nsAString_Init(&text_str, NULL);
    nsres = nsIDOMHTMLScriptElement_GetText(script_elem->nsscript, &text_str);
    nsAString_GetData(&text_str, &text);

    if(NS_FAILED(nsres)) {
        ERR("GetText failed: %08x\n", nsres);
    }else if(*text) {
        parse_elem_text(script_host, script_elem, text);
    }

    nsAString_Finish(&text_str);
}