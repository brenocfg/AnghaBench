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
struct TYPE_4__ {char* url; scalar_t__ written_uncompressed; scalar_t__ written_compressed; scalar_t__ payload_allocated; scalar_t__ payload_size; int /*<<< orphan*/  payload; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ PullJob ;

/* Variables and functions */
 int /*<<< orphan*/  PULL_JOB_INIT ; 
 int /*<<< orphan*/  free (char*) ; 
 int import_url_change_last_component (char*,char*,char**) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int pull_job_begin (TYPE_1__*) ; 

__attribute__((used)) static int pull_job_restart(PullJob *j) {
        int r;
        char *chksum_url = NULL;

        r = import_url_change_last_component(j->url, "SHA256SUMS", &chksum_url);
        if (r < 0)
                return r;

        free(j->url);
        j->url = chksum_url;
        j->state = PULL_JOB_INIT;
        j->payload = mfree(j->payload);
        j->payload_size = 0;
        j->payload_allocated = 0;
        j->written_compressed = 0;
        j->written_uncompressed = 0;

        r = pull_job_begin(j);
        if (r < 0)
                return r;

        return 0;
}