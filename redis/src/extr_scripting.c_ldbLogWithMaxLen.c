#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {scalar_t__ maxlen; int maxlen_hint_sent; } ;

/* Variables and functions */
 TYPE_1__ ldb ; 
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void ldbLogWithMaxLen(sds entry) {
    int trimmed = 0;
    if (ldb.maxlen && sdslen(entry) > ldb.maxlen) {
        sdsrange(entry,0,ldb.maxlen-1);
        entry = sdscatlen(entry," ...",4);
        trimmed = 1;
    }
    ldbLog(entry);
    if (trimmed && ldb.maxlen_hint_sent == 0) {
        ldb.maxlen_hint_sent = 1;
        ldbLog(sdsnew(
        "<hint> The above reply was trimmed. Use 'maxlen 0' to disable trimming."));
    }
}