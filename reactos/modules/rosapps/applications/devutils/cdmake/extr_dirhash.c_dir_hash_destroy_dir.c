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
struct target_file {struct target_file* case_name; struct target_file* normalized_name; struct target_file* target_name; struct target_file* source_name; struct target_file* next; struct target_file* head; struct target_file* child; } ;
struct target_dir_hash {int dummy; } ;
struct target_dir_entry {struct target_dir_entry* case_name; struct target_dir_entry* normalized_name; struct target_dir_entry* target_name; struct target_dir_entry* source_name; struct target_dir_entry* next; struct target_dir_entry* head; struct target_dir_entry* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_entry (struct target_dir_hash*,struct target_file*) ; 
 int /*<<< orphan*/  free (struct target_file*) ; 

__attribute__((used)) static void
dir_hash_destroy_dir(struct target_dir_hash *dh, struct target_dir_entry *de)
{
    struct target_file *tf;
    struct target_dir_entry *te;

    while ((te = de->child))
    {
        de->child = te->next;
        dir_hash_destroy_dir(dh, te);
        free(te);
    }
    while ((tf = de->head))
    {
        de->head = tf->next;
        free(tf->source_name);
        free(tf->target_name);
        free(tf);
    }

    delete_entry(dh, de);
    free(de->normalized_name);
    free(de->case_name);
}