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
struct vlc_logger {int /*<<< orphan*/ * ops; } ;
struct vlc_logger_switch {struct vlc_logger frontend; int /*<<< orphan*/  lock; int /*<<< orphan*/ * backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_log ; 
 struct vlc_logger_switch* malloc (int) ; 
 int /*<<< orphan*/  switch_ops ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vlc_logger *vlc_LogSwitchCreate(void)
{
    struct vlc_logger_switch *logswitch = malloc(sizeof (*logswitch));
    if (unlikely(logswitch == NULL))
        return NULL;

    logswitch->frontend.ops = &switch_ops;
    logswitch->backend = &discard_log;
    vlc_rwlock_init(&logswitch->lock);
    return &logswitch->frontend;
}