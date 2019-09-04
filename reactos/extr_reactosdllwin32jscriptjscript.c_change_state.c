#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ site; TYPE_1__* ctx; } ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  scalar_t__ SCRIPTSTATE ;
typedef  TYPE_2__ JScript ;

/* Variables and functions */
 int /*<<< orphan*/  IActiveScriptSite_OnStateChange (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void change_state(JScript *This, SCRIPTSTATE state)
{
    if(This->ctx->state == state)
        return;

    This->ctx->state = state;
    if(This->site)
        IActiveScriptSite_OnStateChange(This->site, state);
}