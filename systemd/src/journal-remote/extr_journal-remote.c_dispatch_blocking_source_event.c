#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {TYPE_1__ importer; } ;
typedef  TYPE_2__ RemoteSource ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int journal_remote_handle_raw_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_remote_server_global ; 

__attribute__((used)) static int dispatch_blocking_source_event(sd_event_source *event,
                                          void *userdata) {
        RemoteSource *source = userdata;

        return journal_remote_handle_raw_source(event, source->importer.fd, EPOLLIN, journal_remote_server_global);
}