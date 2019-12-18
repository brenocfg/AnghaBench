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
struct target_dir_entry {char* case_name; size_t hashcode; struct target_dir_entry* next_dir_hash_entry; struct target_dir_entry* child; struct target_dir_entry* next; void* normalized_name; struct target_dir_entry* parent; } ;
struct target_dir_hash {struct target_dir_entry** buckets; struct target_dir_entry root; } ;

/* Variables and functions */
 size_t NUM_DIR_HASH_BUCKETS ; 
 struct target_dir_entry* calloc (int,int) ; 
 void* djb_hash (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct target_dir_entry* get_entry_by_normname (struct target_dir_hash*,char const*) ; 
 int /*<<< orphan*/  split_path (char const*,char**,char**) ; 
 void* strdup (char const*) ; 

struct target_dir_entry *
dir_hash_create_dir(struct target_dir_hash *dh, const char *casename, const char *targetnorm)
{
    struct target_dir_entry *de, *parent_de;
    char *parentcase = NULL;
    char *case_name  = NULL;
    char *parentname = NULL;
    struct target_dir_entry **ent;

    if (!dh->root.normalized_name)
    {
        dh->root.normalized_name = strdup("");
        dh->root.case_name = strdup("");
        dh->root.hashcode = djb_hash("");
        dh->buckets[dh->root.hashcode % NUM_DIR_HASH_BUCKETS] = &dh->root;
    }

    /* Check whether the directory was already created and just return it if so */
    de = get_entry_by_normname(dh, targetnorm);
    if (de)
        return de;

    /*
     * If *case_name == '\0' after the following call to split_path(...),
     * for example in the case where casename == "subdir/dir/", then just
     * create the directories "subdir" and "dir" by a recursive call to
     * dir_hash_create_dir(...) and return 'parent_de' instead (see after).
     * We do not (and we never) create a no-name directory inside it.
     */
    split_path(casename, &parentcase, &case_name);
    split_path(targetnorm, &parentname, NULL);
    parent_de = dir_hash_create_dir(dh, parentcase, parentname);
    free(parentname);
    free(parentcase);

    /* See the remark above */
    if (!*case_name)
    {
        free(case_name);
        return parent_de;
    }

    /* Now create the directory */
    de = calloc(1, sizeof(*de));
    de->parent = parent_de;
    de->normalized_name = strdup(targetnorm);
    de->case_name = case_name;
    de->hashcode = djb_hash(targetnorm);

    de->next = parent_de->child;
    parent_de->child = de;

    ent = &dh->buckets[de->hashcode % NUM_DIR_HASH_BUCKETS];
    while (*ent)
        ent = &(*ent)->next_dir_hash_entry;
    *ent = de;

    return de;
}