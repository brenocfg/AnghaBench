#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_5__ {int step; scalar_t__ maxlen_hint_sent; int /*<<< orphan*/  maxlen; int /*<<< orphan*/  cbuf; scalar_t__ luabp; scalar_t__ bpcount; int /*<<< orphan*/  conn; int /*<<< orphan*/  logs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_LUA_DEBUG ; 
 int /*<<< orphan*/  LDB_MAX_LEN_DEFAULT ; 
 TYPE_3__ ldb ; 
 int /*<<< orphan*/  ldbFlushLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 

void ldbEnable(client *c) {
    c->flags |= CLIENT_LUA_DEBUG;
    ldbFlushLog(ldb.logs);
    ldb.conn = c->conn;
    ldb.step = 1;
    ldb.bpcount = 0;
    ldb.luabp = 0;
    sdsfree(ldb.cbuf);
    ldb.cbuf = sdsempty();
    ldb.maxlen = LDB_MAX_LEN_DEFAULT;
    ldb.maxlen_hint_sent = 0;
}