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
struct target_file {char* target_name; void* source_name; struct target_file* next; } ;
struct target_dir_hash {int dummy; } ;
struct target_dir_entry {struct target_file* head; } ;

/* Variables and functions */
 struct target_file* calloc (int,int) ; 
 struct target_dir_entry* dir_hash_create_dir (struct target_dir_hash*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  normalize_dirname (char*) ; 
 int /*<<< orphan*/  split_path (char const*,char**,char**) ; 
 void* strdup (char const*) ; 

struct target_file *
dir_hash_add_file(struct target_dir_hash *dh, const char *source, const char *target)
{
    struct target_file *tf;
    struct target_dir_entry *de;
    char *targetdir  = NULL;
    char *targetfile = NULL;
    char *targetnorm;

    /* First create the directory; check whether the file name is valid and bail out if not */
    split_path(target, &targetdir, &targetfile);
    if (!*targetfile)
    {
        free(targetdir);
        free(targetfile);
        return NULL;
    }
    targetnorm = strdup(targetdir);
    normalize_dirname(targetnorm);
    de = dir_hash_create_dir(dh, targetdir, targetnorm);
    free(targetnorm);
    free(targetdir);

    /* Now add the file */
    tf = calloc(1, sizeof(*tf));
    tf->next = de->head;
    de->head = tf;
    tf->source_name = strdup(source);
    tf->target_name = targetfile;

    return tf;
}