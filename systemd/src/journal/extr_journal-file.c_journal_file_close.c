#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ fd; scalar_t__ hmac; int /*<<< orphan*/  fsprg_seed; int /*<<< orphan*/  fsprg_state; int /*<<< orphan*/  fss_file_size; scalar_t__ fss_file; int /*<<< orphan*/  compress_buffer; int /*<<< orphan*/  chain_cache; scalar_t__ mmap; int /*<<< orphan*/  path; scalar_t__ close_fd; scalar_t__ defrag_on_close; scalar_t__ cache_fd; scalar_t__ post_change_timer; scalar_t__ writable; scalar_t__ seal; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  FS_NOCOW_FL ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_defrag_fd (scalar_t__) ; 
 int /*<<< orphan*/  chattr_fd (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_close (scalar_t__) ; 
 int journal_file_append_tag (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_file_post_change (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_file_set_offline (TYPE_1__*,int) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mmap_cache_free_fd (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mmap_cache_unref (scalar_t__) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_hashmap_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (scalar_t__) ; 
 int /*<<< orphan*/  sd_event_source_disable_unref (scalar_t__) ; 
 scalar_t__ sd_event_source_get_enabled (scalar_t__,int /*<<< orphan*/ *) ; 

JournalFile* journal_file_close(JournalFile *f) {
        if (!f)
                return NULL;

#if HAVE_GCRYPT
        /* Write the final tag */
        if (f->seal && f->writable) {
                int r;

                r = journal_file_append_tag(f);
                if (r < 0)
                        log_error_errno(r, "Failed to append tag when closing journal: %m");
        }
#endif

        if (f->post_change_timer) {
                if (sd_event_source_get_enabled(f->post_change_timer, NULL) > 0)
                        journal_file_post_change(f);

                sd_event_source_disable_unref(f->post_change_timer);
        }

        journal_file_set_offline(f, true);

        if (f->mmap && f->cache_fd)
                mmap_cache_free_fd(f->mmap, f->cache_fd);

        if (f->fd >= 0 && f->defrag_on_close) {

                /* Be friendly to btrfs: turn COW back on again now,
                 * and defragment the file. We won't write to the file
                 * ever again, hence remove all fragmentation, and
                 * reenable all the good bits COW usually provides
                 * (such as data checksumming). */

                (void) chattr_fd(f->fd, 0, FS_NOCOW_FL, NULL);
                (void) btrfs_defrag_fd(f->fd);
        }

        if (f->close_fd)
                safe_close(f->fd);
        free(f->path);

        mmap_cache_unref(f->mmap);

        ordered_hashmap_free_free(f->chain_cache);

#if HAVE_XZ || HAVE_LZ4
        free(f->compress_buffer);
#endif

#if HAVE_GCRYPT
        if (f->fss_file)
                munmap(f->fss_file, PAGE_ALIGN(f->fss_file_size));
        else
                free(f->fsprg_state);

        free(f->fsprg_seed);

        if (f->hmac)
                gcry_md_close(f->hmac);
#endif

        return mfree(f);
}