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
struct TYPE_4__ {int /*<<< orphan*/  device_tree; int /*<<< orphan*/  initrd; int /*<<< orphan*/  efi; int /*<<< orphan*/  kernel; int /*<<< orphan*/  options; int /*<<< orphan*/  architecture; int /*<<< orphan*/  machine_id; int /*<<< orphan*/  version; int /*<<< orphan*/  show_title; int /*<<< orphan*/  title; int /*<<< orphan*/  root; int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ BootEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void boot_entry_free(BootEntry *entry) {
        assert(entry);

        free(entry->id);
        free(entry->path);
        free(entry->root);
        free(entry->title);
        free(entry->show_title);
        free(entry->version);
        free(entry->machine_id);
        free(entry->architecture);
        strv_free(entry->options);
        free(entry->kernel);
        free(entry->efi);
        strv_free(entry->initrd);
        free(entry->device_tree);
}