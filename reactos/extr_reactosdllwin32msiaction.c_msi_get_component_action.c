#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Installed; scalar_t__ num_clients; scalar_t__ ActionRequest; int /*<<< orphan*/  Component; int /*<<< orphan*/  Enabled; } ;
struct TYPE_5__ {scalar_t__ need_rollback; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSICOMPONENT ;
typedef  scalar_t__ INSTALLSTATE ;

/* Variables and functions */
 scalar_t__ INSTALLSTATE_ABSENT ; 
 scalar_t__ INSTALLSTATE_UNKNOWN ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

INSTALLSTATE msi_get_component_action( MSIPACKAGE *package, MSICOMPONENT *comp )
{
    if (!comp->Enabled)
    {
        TRACE("component is disabled: %s\n", debugstr_w(comp->Component));
        return INSTALLSTATE_UNKNOWN;
    }
    if (package->need_rollback) return comp->Installed;
    if (comp->num_clients > 0 && comp->ActionRequest == INSTALLSTATE_ABSENT)
    {
        TRACE("%s has %u clients left\n", debugstr_w(comp->Component), comp->num_clients);
        return INSTALLSTATE_UNKNOWN;
    }
    return comp->ActionRequest;
}