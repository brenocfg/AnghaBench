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
typedef  int /*<<< orphan*/  Writer ;
struct TYPE_4__ {int /*<<< orphan*/ ** sources; int /*<<< orphan*/  active; int /*<<< orphan*/  sources_size; } ;
typedef  int /*<<< orphan*/  RemoteSource ;
typedef  TYPE_1__ RemoteServer ;

/* Variables and functions */
 int /*<<< orphan*/  GREEDY_REALLOC0 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int journal_remote_get_writer (TYPE_1__*,char*,int /*<<< orphan*/ **) ; 
 int log_oom () ; 
 int log_warning_errno (int,char*,char*) ; 
 int /*<<< orphan*/ * source_new (int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_source_for_fd(RemoteServer *s,
                             int fd, char *name, RemoteSource **source) {
        Writer *writer;
        int r;

        /* This takes ownership of name, but only on success. */

        assert(fd >= 0);
        assert(source);

        if (!GREEDY_REALLOC0(s->sources, s->sources_size, fd + 1))
                return log_oom();

        r = journal_remote_get_writer(s, name, &writer);
        if (r < 0)
                return log_warning_errno(r, "Failed to get writer for source %s: %m",
                                         name);

        if (!s->sources[fd]) {
                s->sources[fd] = source_new(fd, false, name, writer);
                if (!s->sources[fd]) {
                        writer_unref(writer);
                        return log_oom();
                }

                s->active++;
        }

        *source = s->sources[fd];
        return 0;
}