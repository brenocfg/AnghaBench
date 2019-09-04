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
typedef  int /*<<< orphan*/  dbuf ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,char*,int) ; 
 int snprintf (char*,int,char*,double) ; 

void addReplyDoubleDistance(client *c, double d) {
    char dbuf[128];
    int dlen = snprintf(dbuf, sizeof(dbuf), "%.4f", d);
    addReplyBulkCBuffer(c, dbuf, dlen);
}