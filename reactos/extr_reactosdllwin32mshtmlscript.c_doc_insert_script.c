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
struct TYPE_4__ {scalar_t__ parse; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int /*<<< orphan*/  HTMLScriptElement ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;

/* Variables and functions */
 TYPE_1__* get_elem_script_host (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_script_elem (TYPE_1__*,int /*<<< orphan*/ *) ; 

void doc_insert_script(HTMLInnerWindow *window, HTMLScriptElement *script_elem)
{
    ScriptHost *script_host;

    script_host = get_elem_script_host(window, script_elem);
    if(!script_host)
        return;

    if(script_host->parse)
        parse_script_elem(script_host, script_elem);
}