#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {int started; int logged_incomplete; scalar_t__ size; int /*<<< orphan*/  path; int /*<<< orphan*/  limit; } ;
typedef  TYPE_1__ ProgressInfo ;

/* Variables and functions */
 int FORMAT_BYTES_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  format_bytes (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_notice (char*) ; 
 int /*<<< orphan*/  ratelimit_below (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void progress_show(ProgressInfo *p) {
        assert(p);

        /* Show progress only every now and then. */
        if (!ratelimit_below(&p->limit))
                return;

        /* Suppress the first message, start with the second one */
        if (!p->started) {
                p->started = true;
                return;
        }

        /* Mention the list is incomplete before showing first output. */
        if (!p->logged_incomplete) {
                log_notice("(Note, file list shown below is incomplete, and is intended as sporadic progress report only.)");
                p->logged_incomplete = true;
        }

        if (p->size == 0)
                log_info("Copying tree, currently at '%s'...", p->path);
        else {
                char buffer[FORMAT_BYTES_MAX];

                log_info("Copying tree, currently at '%s' (@%s)...", p->path, format_bytes(buffer, sizeof(buffer), p->size));
        }
}