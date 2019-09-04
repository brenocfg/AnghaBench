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
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conn*) ; 
 int /*<<< orphan*/  nc_free (struct conn*) ; 

__attribute__((used)) static void
conn_free(struct conn *conn)
{
    log_debug(LOG_VVERB, "free conn %p", conn);
    nc_free(conn);
}