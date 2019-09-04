#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* outer_window; } ;
struct TYPE_12__ {TYPE_2__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  nsscript; } ;
struct TYPE_9__ {scalar_t__ scriptmode; } ;
typedef  int /*<<< orphan*/  ScriptHost ;
typedef  TYPE_3__ HTMLScriptElement ;
typedef  TYPE_4__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_JScript ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SCRIPTMODE_ACTIVESCRIPT ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  get_script_guid (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_script_host (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScriptHost *get_elem_script_host(HTMLInnerWindow *window, HTMLScriptElement *script_elem)
{
    GUID guid;

    if(!get_script_guid(window, script_elem->nsscript, &guid)) {
        WARN("Could not find script GUID\n");
        return NULL;
    }

    if(IsEqualGUID(&CLSID_JScript, &guid)
       && (!window->base.outer_window || window->base.outer_window->scriptmode != SCRIPTMODE_ACTIVESCRIPT)) {
        TRACE("Ignoring JScript\n");
        return NULL;
    }

    return get_script_host(window, &guid);
}