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
typedef  int /*<<< orphan*/  Writer ;
typedef  int /*<<< orphan*/  RemoteSource ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void**) ; 
 int journal_remote_get_writer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  journal_remote_server_global ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ *) ; 
 int log_oom () ; 
 int log_warning_errno (int,char*,char*) ; 
 int /*<<< orphan*/ * source_new (int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_meta(void **connection_cls, int fd, char *hostname) {
        RemoteSource *source;
        Writer *writer;
        int r;

        assert(connection_cls);
        if (*connection_cls)
                return 0;

        r = journal_remote_get_writer(journal_remote_server_global, hostname, &writer);
        if (r < 0)
                return log_warning_errno(r, "Failed to get writer for source %s: %m",
                                         hostname);

        source = source_new(fd, true, hostname, writer);
        if (!source) {
                writer_unref(writer);
                return log_oom();
        }

        log_debug("Added RemoteSource as connection metadata %p", source);

        *connection_cls = source;
        return 0;
}