#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* tar_job; TYPE_3__* signature_job; TYPE_2__* checksum_job; TYPE_1__* settings_job; } ;
typedef  TYPE_5__ TarPull ;
typedef  int TarProgress ;
struct TYPE_11__ {unsigned int progress_percent; } ;
struct TYPE_10__ {int progress_percent; } ;
struct TYPE_9__ {int progress_percent; } ;
struct TYPE_8__ {int progress_percent; } ;

/* Variables and functions */
#define  TAR_COPYING 131 
#define  TAR_DOWNLOADING 130 
#define  TAR_FINALIZING 129 
#define  TAR_VERIFYING 128 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  log_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  sd_notifyf (int,char*,unsigned int) ; 

__attribute__((used)) static void tar_pull_report_progress(TarPull *i, TarProgress p) {
        unsigned percent;

        assert(i);

        switch (p) {

        case TAR_DOWNLOADING: {
                unsigned remain = 85;

                percent = 0;

                if (i->settings_job) {
                        percent += i->settings_job->progress_percent * 5 / 100;
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

                if (i->tar_job)
                        percent += i->tar_job->progress_percent * remain / 100;
                break;
        }

        case TAR_VERIFYING:
                percent = 85;
                break;

        case TAR_FINALIZING:
                percent = 90;
                break;

        case TAR_COPYING:
                percent = 95;
                break;

        default:
                assert_not_reached("Unknown progress state");
        }

        sd_notifyf(false, "X_IMPORT_PROGRESS=%u", percent);
        log_debug("Combined progress %u%%", percent);
}