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
struct TYPE_4__ {struct TYPE_4__* p_next; int /*<<< orphan*/ * psz_help; int /*<<< orphan*/ * psz_longname; int /*<<< orphan*/ * psz_shortname; int /*<<< orphan*/ * psz_name; } ;
typedef  TYPE_1__ libvlc_module_description_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  libvlc_module_description_list_release (TYPE_1__*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_moduledescriptionlist (libvlc_module_description_t *list)
{
    libvlc_module_description_t *module = list;
    while ( module ) {
        assert (strlen (module->psz_name) );
        assert (strlen (module->psz_shortname) );
        assert (module->psz_longname == NULL || strlen (module->psz_longname));
        assert (module->psz_help == NULL || strlen (module->psz_help));
        module = module->p_next;
    }    

    libvlc_module_description_list_release (list);
}