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
struct conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_connq ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ nfree_connq ; 

void
conn_init(void)
{
    log_debug(LOG_DEBUG, "conn size %d", sizeof(struct conn));
    nfree_connq = 0;
    TAILQ_INIT(&free_connq);
}