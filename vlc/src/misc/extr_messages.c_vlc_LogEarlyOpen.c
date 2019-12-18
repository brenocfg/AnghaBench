#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vlc_logger {int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {struct vlc_logger logger; struct vlc_logger* sink; int /*<<< orphan*/ * head; int /*<<< orphan*/ ** tailp; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_logger_early_t ;

/* Variables and functions */
 int /*<<< orphan*/  early_ops ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vlc_logger *vlc_LogEarlyOpen(struct vlc_logger *logger)
{
    vlc_logger_early_t *early = malloc(sizeof (*early));
    if (unlikely(early == NULL))
        return NULL;

    early->logger.ops = &early_ops;
    vlc_mutex_init(&early->lock);
    early->head = NULL;
    early->tailp = &early->head;
    early->sink = logger;
    return &early->logger;
}