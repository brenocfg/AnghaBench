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
typedef  int uint64_t ;
struct TYPE_4__ {int quota_referenced; int written_uncompressed; unsigned int last_percent; int /*<<< orphan*/  progress_ratelimit; } ;
typedef  TYPE_1__ TarExport ;

/* Variables and functions */
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_info (char*,unsigned int) ; 
 int /*<<< orphan*/  ratelimit_below (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_notifyf (int,char*,unsigned int) ; 

__attribute__((used)) static void tar_export_report_progress(TarExport *e) {
        unsigned percent;
        assert(e);

        /* Do we have any quota info? If not, we don't know anything about the progress */
        if (e->quota_referenced == (uint64_t) -1)
                return;

        if (e->written_uncompressed >= e->quota_referenced)
                percent = 100;
        else
                percent = (unsigned) ((e->written_uncompressed * UINT64_C(100)) / e->quota_referenced);

        if (percent == e->last_percent)
                return;

        if (!ratelimit_below(&e->progress_ratelimit))
                return;

        sd_notifyf(false, "X_IMPORT_PROGRESS=%u", percent);
        log_info("Exported %u%%.", percent);

        e->last_percent = percent;
}