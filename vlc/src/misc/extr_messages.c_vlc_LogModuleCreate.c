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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_logger {int /*<<< orphan*/ * ops; } ;
struct vlc_logger_module {struct vlc_logger frontend; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (struct vlc_logger_module*) ; 
 int /*<<< orphan*/  module_ops ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct vlc_logger_module* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_logger_load ; 
 int /*<<< orphan*/ * vlc_module_load (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct vlc_logger_module*) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vlc_logger *vlc_LogModuleCreate(vlc_object_t *parent)
{
    struct vlc_logger_module *module;

    module = vlc_custom_create(parent, sizeof (*module), "logger");
    if (unlikely(module == NULL))
        return NULL;

    /* TODO: module configuration item */
    if (vlc_module_load(VLC_OBJECT(module), "logger", NULL, false,
                        vlc_logger_load, module) == NULL) {
        vlc_object_delete(VLC_OBJECT(module));
        return NULL;
    }

    module->frontend.ops = &module_ops;
    return &module->frontend;
}