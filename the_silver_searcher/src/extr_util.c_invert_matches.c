#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t start; size_t end; } ;
typedef  TYPE_1__ match_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  log_debug (char*,size_t,...) ; 

size_t invert_matches(const char *buf, const size_t buf_len, match_t matches[], size_t matches_len) {
    size_t i;
    size_t match_read_index = 0;
    size_t inverted_match_count = 0;
    size_t inverted_match_start = 0;
    size_t last_line_end = 0;
    int in_inverted_match = TRUE;
    match_t next_match;

    log_debug("Inverting %u matches.", matches_len);

    if (matches_len > 0) {
        next_match = matches[0];
    } else {
        next_match.start = buf_len + 1;
    }

    /* No matches, so the whole buffer is now a match. */
    if (matches_len == 0) {
        matches[0].start = 0;
        matches[0].end = buf_len - 1;
        return 1;
    }

    for (i = 0; i < buf_len; i++) {
        if (i == next_match.start) {
            i = next_match.end - 1;

            match_read_index++;

            if (match_read_index < matches_len) {
                next_match = matches[match_read_index];
            }

            if (in_inverted_match && last_line_end > inverted_match_start) {
                matches[inverted_match_count].start = inverted_match_start;
                matches[inverted_match_count].end = last_line_end - 1;

                inverted_match_count++;
            }

            in_inverted_match = FALSE;
        } else if (i == buf_len - 1 && in_inverted_match) {
            matches[inverted_match_count].start = inverted_match_start;
            matches[inverted_match_count].end = i;

            inverted_match_count++;
        } else if (buf[i] == '\n') {
            last_line_end = i + 1;

            if (!in_inverted_match) {
                inverted_match_start = last_line_end;
            }

            in_inverted_match = TRUE;
        }
    }

    for (i = 0; i < matches_len; i++) {
        log_debug("Inverted match %i start %i end %i.", i, matches[i].start, matches[i].end);
    }

    return inverted_match_count;
}