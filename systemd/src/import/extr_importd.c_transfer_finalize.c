#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ n_canceled; int /*<<< orphan*/  object_path; int /*<<< orphan*/  id; TYPE_1__* manager; } ;
typedef  TYPE_2__ Transfer ;
struct TYPE_7__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int sd_bus_emit_signal (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transfer_send_logs (TYPE_2__*,int) ; 
 int /*<<< orphan*/  transfer_unref (TYPE_2__*) ; 

__attribute__((used)) static int transfer_finalize(Transfer *t, bool success) {
        int r;

        assert(t);

        transfer_send_logs(t, true);

        r = sd_bus_emit_signal(
                        t->manager->bus,
                        "/org/freedesktop/import1",
                        "org.freedesktop.import1.Manager",
                        "TransferRemoved",
                        "uos",
                        t->id,
                        t->object_path,
                        success ? "done" :
                        t->n_canceled > 0 ? "canceled" : "failed");

        if (r < 0)
                log_error_errno(r, "Cannot emit message: %m");

        transfer_unref(t);
        return 0;
}