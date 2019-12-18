#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_event; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ RemoteSource ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  SD_EVENT_ON ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int journal_remote_handle_raw_source (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_remote_server_global ; 
 int /*<<< orphan*/  sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dispatch_raw_source_event(sd_event_source *event,
                                     int fd,
                                     uint32_t revents,
                                     void *userdata) {
        RemoteSource *source = userdata;
        int r;

        assert(source->event);
        assert(source->buffer_event);

        r = journal_remote_handle_raw_source(event, fd, EPOLLIN, journal_remote_server_global);
        if (r == 1)
                /* Might have more data. We need to rerun the handler
                 * until we are sure the buffer is exhausted. */
                sd_event_source_set_enabled(source->buffer_event, SD_EVENT_ON);

        return r;
}