#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  runtime_storage; scalar_t__ runtime_journal; int /*<<< orphan*/  system_storage; scalar_t__ system_journal; scalar_t__ oldest_file_usec; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  do_vacuum (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

int server_vacuum(Server *s, bool verbose) {
        assert(s);

        log_debug("Vacuuming...");

        s->oldest_file_usec = 0;

        if (s->system_journal)
                do_vacuum(s, &s->system_storage, verbose);
        if (s->runtime_journal)
                do_vacuum(s, &s->runtime_storage, verbose);

        return 0;
}