#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_6__ {scalar_t__ pos; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {TYPE_2__ conn; } ;
struct TYPE_7__ {TYPE_1__ io; } ;
typedef  TYPE_3__ rio ;

/* Variables and functions */
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 size_t sdslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ *,scalar_t__,int) ; 

void rioFreeConn(rio *r, sds *remaining) {
    if (remaining && (size_t)r->io.conn.pos < sdslen(r->io.conn.buf)) {
        if (r->io.conn.pos > 0) sdsrange(r->io.conn.buf, r->io.conn.pos, -1);
        *remaining = r->io.conn.buf;
    } else {
        sdsfree(r->io.conn.buf);
        if (remaining) *remaining = NULL;
    }
    r->io.conn.buf = NULL;
}