#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct process {struct module* lmodules; } ;
struct TYPE_2__ {int /*<<< orphan*/  const* LoadedImageName; } ;
struct module {TYPE_1__ module; struct module* next; } ;
typedef  int /*<<< orphan*/  const WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* get_filename (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

struct module* module_is_already_loaded(const struct process* pcs, const WCHAR* name)
{
    struct module*      module;
    const WCHAR*        filename;

    /* first compare the loaded image name... */
    for (module = pcs->lmodules; module; module = module->next)
    {
        if (!strcmpiW(name, module->module.LoadedImageName))
            return module;
    }
    /* then compare the standard filenames (without the path) ... */
    filename = get_filename(name, NULL);
    for (module = pcs->lmodules; module; module = module->next)
    {
        if (!strcmpiW(filename, get_filename(module->module.LoadedImageName, NULL)))
            return module;
    }
    SetLastError(ERROR_INVALID_NAME);
    return NULL;
}