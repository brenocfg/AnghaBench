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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

void timeCommand(client *c) {
    struct timeval tv;

    /* gettimeofday() can only fail if &tv is a bad address so we
     * don't check for errors. */
    gettimeofday(&tv,NULL);
    addReplyArrayLen(c,2);
    addReplyBulkLongLong(c,tv.tv_sec);
    addReplyBulkLongLong(c,tv.tv_usec);
}