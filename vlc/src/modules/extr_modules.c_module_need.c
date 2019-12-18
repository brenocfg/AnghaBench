#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int force; int /*<<< orphan*/  logger; } ;
typedef  TYPE_1__ vlc_object_t ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  generic_start ; 
 int /*<<< orphan*/  module_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Create (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_module_load (int /*<<< orphan*/ ,char const*,char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

module_t *module_need(vlc_object_t *obj, const char *cap, const char *name,
                      bool strict)
{
    const bool b_force_backup = obj->force; /* FIXME: remove this */
    module_t *module = vlc_module_load(obj->logger, cap, name, strict,
                                       generic_start, obj);
    if (module != NULL) {
        var_Create(obj, "module-name", VLC_VAR_STRING);
        var_SetString(obj, "module-name", module_get_object(module));
    }

    obj->force = b_force_backup;
    return module;
}