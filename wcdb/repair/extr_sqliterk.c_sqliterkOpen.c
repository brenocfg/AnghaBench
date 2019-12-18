#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_cipher_conf ;
struct TYPE_6__ {int /*<<< orphan*/  onParseColumn; int /*<<< orphan*/  onEndParseBtree; int /*<<< orphan*/  onBeginParseBtree; int /*<<< orphan*/  onEndParsePage; int /*<<< orphan*/  onBeginParsePage; } ;
struct TYPE_7__ {int recursive; TYPE_1__ listen; int /*<<< orphan*/  pager; } ;
typedef  TYPE_2__ sqliterk ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_NOMEM ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkClose (TYPE_2__*) ; 
 int /*<<< orphan*/  sqliterkNotify_onBeginParseBtree ; 
 int /*<<< orphan*/  sqliterkNotify_onBeginParsePage ; 
 int /*<<< orphan*/  sqliterkNotify_onEndParseBtree ; 
 int /*<<< orphan*/  sqliterkNotify_onEndParsePage ; 
 int /*<<< orphan*/  sqliterkNotify_onParseColumn ; 
 int /*<<< orphan*/  sqliterkOSError (int,char*,int) ; 
 int /*<<< orphan*/  sqliterkOSInfo (int,char*,char const*,char*) ; 
 TYPE_2__* sqliterkOSMalloc (int) ; 
 int sqliterkPagerOpen (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int sqliterkOpen(const char *path,
                 const sqliterk_cipher_conf *cipher,
                 sqliterk **rk)
{
    if (!rk) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    sqliterk *therk = sqliterkOSMalloc(sizeof(sqliterk));
    if (!therk) {
        rc = SQLITERK_NOMEM;
        sqliterkOSError(rc, "Not enough memory, required: %zu bytes",
                        sizeof(sqliterk));
        goto sqliterkOpen_Failed;
    }

    rc = sqliterkPagerOpen(path, cipher, &therk->pager);
    if (rc != SQLITERK_OK) {
        goto sqliterkOpen_Failed;
    }

    therk->listen.onBeginParsePage = sqliterkNotify_onBeginParsePage;
    therk->listen.onEndParsePage = sqliterkNotify_onEndParsePage;
    therk->listen.onBeginParseBtree = sqliterkNotify_onBeginParseBtree;
    therk->listen.onEndParseBtree = sqliterkNotify_onEndParseBtree;
    therk->listen.onParseColumn = sqliterkNotify_onParseColumn;
    therk->recursive = 1;

    *rk = therk;
    sqliterkOSInfo(SQLITERK_OK, "RepairKit on '%s' opened, %s.", path,
                   cipher ? "encrypted" : "plain-text");
    return SQLITERK_OK;

sqliterkOpen_Failed:
    if (therk) {
        sqliterkClose(therk);
    }
    *rk = NULL;
    return rc;
}