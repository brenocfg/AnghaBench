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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* deactivate ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_get_object (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_objres_clear (int /*<<< orphan*/ *) ; 

void module_unneed(vlc_object_t *obj, module_t *module)
{
    msg_Dbg(obj, "removing module \"%s\"", module_get_object(module));
    var_Destroy(obj, "module-name");

    if (module->deactivate != NULL)
        module->deactivate(obj);

    vlc_objres_clear(obj);
}