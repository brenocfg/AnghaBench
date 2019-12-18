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
struct TYPE_7__ {int unique_file_lost; int fields_file_lost; int /*<<< orphan*/  current_invalidate_counter; struct TYPE_7__* fields_file; scalar_t__ fields_offset; int /*<<< orphan*/  path; int /*<<< orphan*/  files; struct TYPE_7__* unique_file; scalar_t__ unique_offset; scalar_t__ current_field; struct TYPE_7__* current_file; } ;
typedef  TYPE_1__ sd_journal ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_file_close (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 void* ordered_hashmap_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_file_real(sd_journal *j, JournalFile *f) {
        assert(j);
        assert(f);

        (void) ordered_hashmap_remove(j->files, f->path);

        log_debug("File %s removed.", f->path);

        if (j->current_file == f) {
                j->current_file = NULL;
                j->current_field = 0;
        }

        if (j->unique_file == f) {
                /* Jump to the next unique_file or NULL if that one was last */
                j->unique_file = ordered_hashmap_next(j->files, j->unique_file->path);
                j->unique_offset = 0;
                if (!j->unique_file)
                        j->unique_file_lost = true;
        }

        if (j->fields_file == f) {
                j->fields_file = ordered_hashmap_next(j->files, j->fields_file->path);
                j->fields_offset = 0;
                if (!j->fields_file)
                        j->fields_file_lost = true;
        }

        (void) journal_file_close(f);

        j->current_invalidate_counter++;
}