#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t n_devices; int /*<<< orphan*/  match_parent; int /*<<< orphan*/  match_tag; int /*<<< orphan*/  match_sysname; int /*<<< orphan*/  match_property; int /*<<< orphan*/  nomatch_sysattr; int /*<<< orphan*/  match_sysattr; int /*<<< orphan*/  nomatch_subsystem; int /*<<< orphan*/  match_subsystem; int /*<<< orphan*/ * devices; } ;
typedef  TYPE_1__ sd_device_enumerator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_free_free_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_device_enumerator *device_enumerator_free(sd_device_enumerator *enumerator) {
        size_t i;

        assert(enumerator);

        for (i = 0; i < enumerator->n_devices; i++)
                sd_device_unref(enumerator->devices[i]);

        free(enumerator->devices);
        set_free_free(enumerator->match_subsystem);
        set_free_free(enumerator->nomatch_subsystem);
        hashmap_free_free_free(enumerator->match_sysattr);
        hashmap_free_free_free(enumerator->nomatch_sysattr);
        hashmap_free_free_free(enumerator->match_property);
        set_free_free(enumerator->match_sysname);
        set_free_free(enumerator->match_tag);
        set_free_free(enumerator->match_parent);

        return mfree(enumerator);
}