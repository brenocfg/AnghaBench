#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ mmap; scalar_t__ hashmap_key; TYPE_1__* server; TYPE_7__* journal; } ;
typedef  TYPE_2__ Writer ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {int /*<<< orphan*/  writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  journal_file_close (TYPE_7__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mmap_cache_unref (scalar_t__) ; 

__attribute__((used)) static Writer* writer_free(Writer *w) {
        if (!w)
                return NULL;

        if (w->journal) {
                log_debug("Closing journal file %s.", w->journal->path);
                journal_file_close(w->journal);
        }

        if (w->server && w->hashmap_key)
                hashmap_remove(w->server->writers, w->hashmap_key);

        free(w->hashmap_key);

        if (w->mmap)
                mmap_cache_unref(w->mmap);

        return mfree(w);
}