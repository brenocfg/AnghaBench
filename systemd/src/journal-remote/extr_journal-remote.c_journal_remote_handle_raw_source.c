#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_10__ {int fd; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  active; int /*<<< orphan*/  seal; int /*<<< orphan*/  compress; TYPE_1__** sources; scalar_t__ sources_size; } ;
struct TYPE_8__ {TYPE_6__ importer; } ;
typedef  TYPE_1__ RemoteSource ;
typedef  TYPE_2__ RemoteServer ;

/* Variables and functions */
 int E2BIG ; 
 int EAGAIN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t journal_importer_bytes_remaining (TYPE_6__*) ; 
 scalar_t__ journal_importer_eof (TYPE_6__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  log_notice (char*,...) ; 
 int process_source (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_source (TYPE_2__*,int) ; 

int journal_remote_handle_raw_source(
                sd_event_source *event,
                int fd,
                uint32_t revents,
                RemoteServer *s) {

        RemoteSource *source;
        int r;

        /* Returns 1 if there might be more data pending,
         * 0 if data is currently exhausted, negative on error.
         */

        assert(fd >= 0 && fd < (ssize_t) s->sources_size);
        source = s->sources[fd];
        assert(source->importer.fd == fd);

        r = process_source(source, s->compress, s->seal);
        if (journal_importer_eof(&source->importer)) {
                size_t remaining;

                log_debug("EOF reached with source %s (fd=%d)",
                          source->importer.name, source->importer.fd);

                remaining = journal_importer_bytes_remaining(&source->importer);
                if (remaining > 0)
                        log_notice("Premature EOF. %zu bytes lost.", remaining);
                remove_source(s, source->importer.fd);
                log_debug("%zu active sources remaining", s->active);
                return 0;
        } else if (r == -E2BIG) {
                log_notice("Entry with too many fields, skipped");
                return 1;
        } else if (r == -ENOBUFS) {
                log_notice("Entry too big, skipped");
                return 1;
        } else if (r == -EAGAIN) {
                return 0;
        } else if (r < 0) {
                log_debug_errno(r, "Closing connection: %m");
                remove_source(s, fd);
                return 0;
        } else
                return 1;
}