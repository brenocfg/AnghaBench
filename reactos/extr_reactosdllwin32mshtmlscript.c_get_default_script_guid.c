#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  guid; } ;
struct TYPE_4__ {int /*<<< orphan*/  script_hosts; } ;
typedef  TYPE_1__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_JScript ; 
 TYPE_3__* LIST_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScriptHost ; 
 int /*<<< orphan*/  entry ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GUID get_default_script_guid(HTMLInnerWindow *window)
{
    /* If not specified, we should use very first script host that was created for the page (or JScript if none) */
    return list_empty(&window->script_hosts)
        ? CLSID_JScript
        : LIST_ENTRY(list_head(&window->script_hosts), ScriptHost, entry)->guid;
}