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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  (* TraverseFSTreeCallback ) (int /*<<< orphan*/ *,char const*,int,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  SeafFSManager ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEAF_METADATA_TYPE_FILE ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
traverse_file (SeafFSManager *mgr,
               const char *repo_id,
               int version,
               const char *id,
               TraverseFSTreeCallback callback,
               void *user_data,
               gboolean skip_errors)
{
    gboolean stop = FALSE;

    if (memcmp (id, EMPTY_SHA1, 40) == 0)
        return 0;

    if (!callback (mgr, repo_id, version, id, SEAF_METADATA_TYPE_FILE, user_data, &stop) &&
        !skip_errors)
        return -1;

    return 0;
}