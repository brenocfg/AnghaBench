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
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  sd_journal ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  OutputMode ;
typedef  int OutputFlags ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ESTALE ; 
 int OUTPUT_FOLLOW ; 
 int OUTPUT_WARN_CUTOFF ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  _OUTPUT_MODE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  maybe_print_begin_newline (int /*<<< orphan*/ *,int*) ; 
 int sd_id128_get_boot (int /*<<< orphan*/ *) ; 
 int sd_journal_get_cutoff_monotonic_usec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int sd_journal_get_monotonic_usec (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int sd_journal_next (int /*<<< orphan*/ *) ; 
 int sd_journal_previous_skip (int /*<<< orphan*/ *,unsigned int) ; 
 int sd_journal_seek_tail (int /*<<< orphan*/ *) ; 
 int sd_journal_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int show_journal_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

int show_journal(
                FILE *f,
                sd_journal *j,
                OutputMode mode,
                unsigned n_columns,
                usec_t not_before,
                unsigned how_many,
                OutputFlags flags,
                bool *ellipsized) {

        int r;
        unsigned line = 0;
        bool need_seek = false;
        int warn_cutoff = flags & OUTPUT_WARN_CUTOFF;

        assert(j);
        assert(mode >= 0);
        assert(mode < _OUTPUT_MODE_MAX);

        if (how_many == (unsigned) -1)
                need_seek = true;
        else {
                /* Seek to end */
                r = sd_journal_seek_tail(j);
                if (r < 0)
                        return log_error_errno(r, "Failed to seek to tail: %m");

                r = sd_journal_previous_skip(j, how_many);
                if (r < 0)
                        return log_error_errno(r, "Failed to skip previous: %m");
        }

        for (;;) {
                for (;;) {
                        usec_t usec;

                        if (need_seek) {
                                r = sd_journal_next(j);
                                if (r < 0)
                                        return log_error_errno(r, "Failed to iterate through journal: %m");
                        }

                        if (r == 0)
                                break;

                        need_seek = true;

                        if (not_before > 0) {
                                r = sd_journal_get_monotonic_usec(j, &usec, NULL);

                                /* -ESTALE is returned if the
                                   timestamp is not from this boot */
                                if (r == -ESTALE)
                                        continue;
                                else if (r < 0)
                                        return log_error_errno(r, "Failed to get journal time: %m");

                                if (usec < not_before)
                                        continue;
                        }

                        line++;
                        maybe_print_begin_newline(f, &flags);

                        r = show_journal_entry(f, j, mode, n_columns, flags, NULL, NULL, ellipsized);
                        if (r < 0)
                                return r;
                }

                if (warn_cutoff && line < how_many && not_before > 0) {
                        sd_id128_t boot_id;
                        usec_t cutoff = 0;

                        /* Check whether the cutoff line is too early */

                        r = sd_id128_get_boot(&boot_id);
                        if (r < 0)
                                return log_error_errno(r, "Failed to get boot id: %m");

                        r = sd_journal_get_cutoff_monotonic_usec(j, boot_id, &cutoff, NULL);
                        if (r < 0)
                                return log_error_errno(r, "Failed to get journal cutoff time: %m");

                        if (r > 0 && not_before < cutoff) {
                                maybe_print_begin_newline(f, &flags);
                                fprintf(f, "Warning: Journal has been rotated since unit was started. Log output is incomplete or unavailable.\n");
                        }

                        warn_cutoff = false;
                }

                if (!(flags & OUTPUT_FOLLOW))
                        break;

                r = sd_journal_wait(j, USEC_INFINITY);
                if (r < 0)
                        return log_error_errno(r, "Failed to wait for journal: %m");

        }

        return 0;
}