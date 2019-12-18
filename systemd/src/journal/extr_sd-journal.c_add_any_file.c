#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct TYPE_17__ {scalar_t__ toplevel_fd; int /*<<< orphan*/  current_invalidate_counter; int /*<<< orphan*/  generation; int /*<<< orphan*/  files; int /*<<< orphan*/  mmap; } ;
typedef  TYPE_2__ sd_journal ;
struct TYPE_16__ {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct TYPE_18__ {char const* path; int close_fd; int /*<<< orphan*/  fd; int /*<<< orphan*/  last_seen_generation; TYPE_1__ last_stat; } ;
typedef  TYPE_3__ JournalFile ;

/* Variables and functions */
 int ETOOMANYREFS ; 
 scalar_t__ JOURNAL_FILES_MAX ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  check_network (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int fd_nonblock (int,int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  journal_file_close (TYPE_3__*) ; 
 int journal_file_open (int,char const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int journal_put_error (TYPE_2__*,int,char const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int log_debug_errno (int,char*,char const*) ; 
 int open (char const*,int) ; 
 int openat (scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ordered_hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 int ordered_hashmap_put (int /*<<< orphan*/ ,char const*,TYPE_3__*) ; 
 scalar_t__ ordered_hashmap_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_file_real (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  skip_slash (char const*) ; 
 int stat_verify_regular (struct stat*) ; 
 int /*<<< orphan*/  track_file_disposition (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int add_any_file(
                sd_journal *j,
                int fd,
                const char *path) {

        bool close_fd = false;
        JournalFile *f;
        struct stat st;
        int r, k;

        assert(j);
        assert(fd >= 0 || path);

        if (fd < 0) {
                if (j->toplevel_fd >= 0)
                        /* If there's a top-level fd defined make the path relative, explicitly, since otherwise
                         * openat() ignores the first argument. */

                        fd = openat(j->toplevel_fd, skip_slash(path), O_RDONLY|O_CLOEXEC|O_NONBLOCK);
                else
                        fd = open(path, O_RDONLY|O_CLOEXEC|O_NONBLOCK);
                if (fd < 0) {
                        r = log_debug_errno(errno, "Failed to open journal file %s: %m", path);
                        goto finish;
                }

                close_fd = true;

                r = fd_nonblock(fd, false);
                if (r < 0) {
                        r = log_debug_errno(errno, "Failed to turn off O_NONBLOCK for %s: %m", path);
                        goto finish;
                }
        }

        if (fstat(fd, &st) < 0) {
                r = log_debug_errno(errno, "Failed to fstat file '%s': %m", path);
                goto finish;
        }

        r = stat_verify_regular(&st);
        if (r < 0) {
                log_debug_errno(r, "Refusing to open '%s', as it is not a regular file.", path);
                goto finish;
        }

        f = ordered_hashmap_get(j->files, path);
        if (f) {
                if (f->last_stat.st_dev == st.st_dev &&
                    f->last_stat.st_ino == st.st_ino) {

                        /* We already track this file, under the same path and with the same device/inode numbers, it's
                         * hence really the same. Mark this file as seen in this generation. This is used to GC old
                         * files in process_q_overflow() to detect journal files that are still there and discern them
                         * from those which are gone. */

                        f->last_seen_generation = j->generation;
                        r = 0;
                        goto finish;
                }

                /* So we tracked a file under this name, but it has a different inode/device. In that case, it got
                 * replaced (probably due to rotation?), let's drop it hence from our list. */
                remove_file_real(j, f);
                f = NULL;
        }

        if (ordered_hashmap_size(j->files) >= JOURNAL_FILES_MAX) {
                log_debug("Too many open journal files, not adding %s.", path);
                r = -ETOOMANYREFS;
                goto finish;
        }

        r = journal_file_open(fd, path, O_RDONLY, 0, false, 0, false, NULL, j->mmap, NULL, NULL, &f);
        if (r < 0) {
                log_debug_errno(r, "Failed to open journal file %s: %m", path);
                goto finish;
        }

        /* journal_file_dump(f); */

        r = ordered_hashmap_put(j->files, f->path, f);
        if (r < 0) {
                f->close_fd = false; /* make sure journal_file_close() doesn't close the caller's fd (or our own). We'll let the caller do that, or ourselves */
                (void) journal_file_close(f);
                goto finish;
        }

        close_fd = false; /* the fd is now owned by the JournalFile object */

        f->last_seen_generation = j->generation;

        track_file_disposition(j, f);
        check_network(j, f->fd);

        j->current_invalidate_counter++;

        log_debug("File %s added.", f->path);

        r = 0;

finish:
        if (close_fd)
                safe_close(fd);

        if (r < 0) {
                k = journal_put_error(j, r, path);
                if (k < 0)
                        return k;
        }

        return r;
}