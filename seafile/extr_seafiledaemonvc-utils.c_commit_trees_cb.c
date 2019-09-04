#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct cache_tree_sub {TYPE_1__* cache_tree; } ;
struct cache_tree {scalar_t__ mtime; int /*<<< orphan*/  sha1; } ;
struct TYPE_19__ {scalar_t__ sec; } ;
struct cache_entry {int ce_flags; char* name; unsigned char* sha1; unsigned int ce_mode; int ce_size; char* modifier; TYPE_2__ ce_mtime; } ;
typedef  scalar_t__ guint64 ;
typedef  int gint64 ;
struct TYPE_22__ {TYPE_3__* data; struct TYPE_22__* next; } ;
struct TYPE_21__ {int /*<<< orphan*/  dir_id; } ;
struct TYPE_20__ {scalar_t__ mtime; } ;
struct TYPE_18__ {int entry_count; unsigned char* sha1; scalar_t__ mtime; } ;
struct TYPE_17__ {int /*<<< orphan*/  fs_mgr; } ;
typedef  TYPE_3__ SeafDirent ;
typedef  TYPE_4__ SeafDir ;
typedef  TYPE_5__ GList ;

/* Variables and functions */
 int CE_REMOVE ; 
 unsigned int S_IFDIR ; 
 struct cache_tree_sub* cache_tree_find_subtree (struct cache_tree*,char const*,int,int /*<<< orphan*/ ) ; 
 int ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  compare_dirents ; 
 int /*<<< orphan*/  dir_version_from_repo_version (int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_5__* g_list_prepend (TYPE_5__*,TYPE_3__*) ; 
 TYPE_5__* g_list_sort (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 char* g_strndup (char const*,int) ; 
 int /*<<< orphan*/  hex_to_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char const*,char*,int) ; 
 TYPE_11__* seaf ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_4__*) ; 
 TYPE_4__* seaf_dir_new (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_dir_save (int /*<<< orphan*/ ,char const*,int,TYPE_4__*) ; 
 TYPE_3__* seaf_dirent_new (int /*<<< orphan*/ ,char*,unsigned int,char*,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  seaf_fs_manager_object_exists (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 

int
commit_trees_cb (const char *repo_id, int version,
                 const char *worktree,
                 struct cache_tree *it, struct cache_entry **cache,
                 int entries, const char *base, int baselen)
{
    SeafDir *seaf_dir;
    GList *dirents = NULL, *ptr;
    int i;

    for (i = 0; i < entries; i++) {
        SeafDirent *seaf_dent;
        char *name;
        struct cache_entry *ce = cache[i];
        struct cache_tree_sub *sub;
        const char *path, *slash;
        int pathlen, entlen;
        const unsigned char *sha1;
        char hex[41];
        unsigned mode;
        guint64 mtime;
        gint64 size;
        char *modifier;

        if (ce->ce_flags & CE_REMOVE)
            continue; /* entry being removed */

        path = ce->name;
        pathlen = ce_namelen(ce);
        if (pathlen <= baselen || memcmp(base, path, baselen))
            break; /* at the end of this level */

        slash = strchr(path + baselen, '/');
        if (slash) {
            entlen = slash - (path + baselen);
            sub = cache_tree_find_subtree(it, path + baselen, entlen, 0);
            g_return_val_if_fail (sub != NULL, -1);
            /* Skip cache entries in the sub level. */
            i += sub->cache_tree->entry_count - 1;

            sha1 = sub->cache_tree->sha1;
            mtime = sub->cache_tree->mtime;
            mode = S_IFDIR;
            name = g_strndup(path + baselen, entlen);

            rawdata_to_hex (sha1, hex, 20);
            seaf_dent = seaf_dirent_new (dir_version_from_repo_version(version),
                                         hex, mode, name, mtime, NULL, -1);
            g_free(name);

            dirents = g_list_prepend (dirents, seaf_dent);
        } else {
            sha1 = ce->sha1;
            mode = ce->ce_mode;
            mtime = ce->ce_mtime.sec;
            size = ce->ce_size;
            modifier = ce->modifier;
            entlen = pathlen - baselen;
            name = g_strndup(path + baselen, entlen);
            rawdata_to_hex (sha1, hex, 20);

            if (version > 0) {
                seaf_dent =
                    seaf_dirent_new (dir_version_from_repo_version(version),
                                     hex, mode, name, mtime, modifier, size);
            } else {
                seaf_dent = seaf_dirent_new (0, hex, mode, name, 0, NULL, -1);
            }

            g_free(name);

            dirents = g_list_prepend (dirents, seaf_dent);
        }

#if DEBUG
        fprintf(stderr, "cache-tree update-one %o %.*s\n",
                mode, entlen, path + baselen);
#endif
    }

    /* Sort dirents in descending order. */
    dirents = g_list_sort (dirents, compare_dirents);

    seaf_dir = seaf_dir_new (NULL, dirents, dir_version_from_repo_version(version));
    hex_to_rawdata (seaf_dir->dir_id, it->sha1, 20);

    /* Dir's mtime is the latest of all dir entires. */
    guint64 dir_mtime = 0;
    SeafDirent *dent;
    for (ptr = dirents; ptr; ptr = ptr->next) {
        dent = ptr->data;
        if (dent->mtime > dir_mtime)
            dir_mtime = dent->mtime;
    }
    it->mtime = dir_mtime;

    if (!seaf_fs_manager_object_exists (seaf->fs_mgr,
                                        repo_id, version,
                                        seaf_dir->dir_id))
        seaf_dir_save (seaf->fs_mgr, repo_id, version, seaf_dir);

#if DEBUG
    for (p = dirents; p; p = p->next) {
        SeafDirent *tmp = (SeafDirent *)p->data;
        fprintf(stderr, "dump dirent name %s id %s\n", tmp->name, tmp->id);
    }
#endif

    seaf_dir_free (seaf_dir);
    return 0;
}