#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {char const* path; } ;
struct TYPE_9__ {int /*<<< orphan*/  threshold_bytes; int /*<<< orphan*/  enabled; } ;
struct TYPE_10__ {int /*<<< orphan*/  deferred_closes; TYPE_1__ compress; } ;
typedef  TYPE_2__ Server ;
typedef  TYPE_3__ JournalFile ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int journal_file_rotate (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  server_add_acls (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_rotate(
                Server *s,
                JournalFile **f,
                const char* name,
                bool seal,
                uint32_t uid) {

        int r;
        assert(s);

        if (!*f)
                return -EINVAL;

        r = journal_file_rotate(f, s->compress.enabled, s->compress.threshold_bytes, seal, s->deferred_closes);
        if (r < 0) {
                if (*f)
                        return log_error_errno(r, "Failed to rotate %s: %m", (*f)->path);
                else
                        return log_error_errno(r, "Failed to create new %s journal: %m", name);
        }

        server_add_acls(*f, uid);

        return r;
}