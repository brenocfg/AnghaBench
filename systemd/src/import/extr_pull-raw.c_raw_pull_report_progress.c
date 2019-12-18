#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* raw_job; TYPE_4__* signature_job; TYPE_3__* checksum_job; TYPE_2__* roothash_job; TYPE_1__* settings_job; } ;
struct TYPE_13__ {unsigned int progress_percent; } ;
struct TYPE_12__ {int progress_percent; } ;
struct TYPE_11__ {int progress_percent; } ;
struct TYPE_10__ {int progress_percent; } ;
struct TYPE_9__ {int progress_percent; } ;
typedef  TYPE_6__ RawPull ;
typedef  int RawProgress ;

/* Variables and functions */
#define  RAW_COPYING 132 
#define  RAW_DOWNLOADING 131 
#define  RAW_FINALIZING 130 
#define  RAW_UNPACKING 129 
#define  RAW_VERIFYING 128 
 int /*<<< orphan*/  assert (TYPE_6__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  log_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  sd_notifyf (int,char*,unsigned int) ; 

__attribute__((used)) static void raw_pull_report_progress(RawPull *i, RawProgress p) {
        unsigned percent;

        assert(i);

        switch (p) {

        case RAW_DOWNLOADING: {
                unsigned remain = 80;

                percent = 0;

                if (i->settings_job) {
                        percent += i->settings_job->progress_percent * 5 / 100;
                        remain -= 5;
                }

                if (i->roothash_job) {
                        percent += i->roothash_job->progress_percent * 5 / 100;
                        remain -= 5;
                }

                if (i->checksum_job) {
                        percent += i->checksum_job->progress_percent * 5 / 100;
                        remain -= 5;
                }

                if (i->signature_job) {
                        percent += i->signature_job->progress_percent * 5 / 100;
                        remain -= 5;
                }

                if (i->raw_job)
                        percent += i->raw_job->progress_percent * remain / 100;
                break;
        }

        case RAW_VERIFYING:
                percent = 80;
                break;

        case RAW_UNPACKING:
                percent = 85;
                break;

        case RAW_FINALIZING:
                percent = 90;
                break;

        case RAW_COPYING:
                percent = 95;
                break;

        default:
                assert_not_reached("Unknown progress state");
        }

        sd_notifyf(false, "X_IMPORT_PROGRESS=%u", percent);
        log_debug("Combined progress %u%%", percent);
}