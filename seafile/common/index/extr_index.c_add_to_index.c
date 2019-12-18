#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct TYPE_8__ {scalar_t__ sec; } ;
struct TYPE_7__ {scalar_t__ sec; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  modifier; int /*<<< orphan*/  sha1; TYPE_2__ ce_ctime; TYPE_1__ ce_mtime; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_9__ {scalar_t__ st_ctime; scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_3__ SeafStat ;
typedef  scalar_t__ (* IndexCB ) (char const*,int,char const*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int ABS (scalar_t__) ; 
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int CE_ADDED ; 
 unsigned int CE_MATCH_IGNORE_SKIP_WORKTREE ; 
 unsigned int CE_MATCH_IGNORE_VALID ; 
 unsigned int CE_MATCH_RACY_IS_DIRTY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ add_index_entry (struct index_state*,struct cache_entry*,int) ; 
 int cache_entry_size (int) ; 
 struct cache_entry* calloc (int,int) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry*) ; 
 int /*<<< orphan*/  create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_stat_cache_info (struct cache_entry*,TYPE_3__*) ; 
 int /*<<< orphan*/  free (struct cache_entry*) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  ie_match_stat (struct cache_entry*,TYPE_3__*,unsigned int) ; 
 struct cache_entry* index_name_exists (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  remove_file_from_index (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 int strlen (char const*) ; 

int add_to_index(const char *repo_id,
                 int version,
                 struct index_state *istate,
                 const char *path,
                 const char *full_path,
                 SeafStat *st,
                 int flags,
                 SeafileCrypt *crypt,
                 IndexCB index_cb,
                 const char *modifier,
                 gboolean *added)
{
    int size, namelen;
    mode_t st_mode = st->st_mode;
    struct cache_entry *ce, *alias;
    unsigned char sha1[20];
    unsigned ce_option = CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE|CE_MATCH_RACY_IS_DIRTY;
    int add_option = (ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE);

    *added = FALSE;

    if (!S_ISREG(st_mode) && !S_ISLNK(st_mode) && !S_ISDIR(st_mode)) {
        seaf_warning("%s: can only add regular files, symbolic links or git-directories\n", path);
        return -1;
    }

    namelen = strlen(path);
    /* if (S_ISDIR(st_mode)) { */
    /*     while (namelen && path[namelen-1] == '/') */
    /*         namelen--; */
    /* } */
    size = cache_entry_size(namelen);
    ce = calloc(1, size);
    memcpy(ce->name, path, namelen);
    ce->ce_flags = namelen;
    fill_stat_cache_info(ce, st);

    ce->ce_mode = create_ce_mode(st_mode);

    alias = index_name_exists(istate, ce->name, ce_namelen(ce), 0);
    if (alias) {
        if (!ce_stage(alias) && !ie_match_stat(alias, st, ce_option)) {
            free(ce);
            return 0;
        }
    } else {
#if defined WIN32 || defined __APPLE__
        alias = index_name_exists (istate, ce->name, ce_namelen(ce), 1);
        /* If file exists case-insensitively but doesn't exist case-sensitively,
         * that file is actually being renamed.
         */
        if (alias) {
            remove_file_from_index (istate, alias->name);
            alias = NULL;
        }
#endif
    }

#ifdef WIN32
    /* On Windows, no 'x' bit in file mode.
     * To prevent overwriting 'x' bit, we directly use existing ce mode. 
     */
    if (alias)
        ce->ce_mode = alias->ce_mode;
#endif

#if 0
#ifdef WIN32
    /* Fix daylight saving time bug on Windows.
     * See http://www.codeproject.com/Articles/1144/Beating-the-Daylight-Savings-Time-bug-and-getting
     * If ce and wt timestamp has a 1 hour gap, it may be affected by the bug.
     * We then compare the file's id with the id in ce. If they're the same,
     * we don't need to copy the blocks again. Only update the index.
     */
    if (alias && !ce_stage(alias) &&
        (ABS(alias->ce_mtime.sec - st->st_mtime) == 3600 ||
         ABS(alias->ce_ctime.sec - st->st_ctime) == 3600)) {
        if (index_cb (repo_id, version, full_path, sha1, crypt, FALSE) < 0) {
            free (ce);
            return 0;
        }
        if (memcmp (alias->sha1, sha1, 20) == 0)
            goto update_index;
    }
#endif
#endif  /* 0 */

    if (index_cb (repo_id, version, full_path, sha1, crypt, TRUE) < 0) {
        free (ce);
        return -1;
    }

    memcpy (ce->sha1, sha1, 20);
    ce->ce_flags |= CE_ADDED;
    ce->modifier = g_strdup(modifier);

    if (add_index_entry(istate, ce, add_option)) {
        seaf_warning("unable to add %s to index\n",path);
        return -1;
    }

    /* As long as the timestamp or mode is changed, we consider
       the cache enrty as changed. This has been tested by ie_match_stat().
    */
    *added = TRUE;

    return 0;
}