#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {int /*<<< orphan*/  pLog; TYPE_3__* pReal; } ;
typedef  TYPE_2__ VLogFile ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xFetch ) (TYPE_3__*,int /*<<< orphan*/ ,int,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VLOG_OP_FETCH ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  vlogLogPrint (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int) ; 
 scalar_t__ vlog_time () ; 

__attribute__((used)) static int
vlogFetch(sqlite3_file *pFile, sqlite3_int64 iOff, int nAmt, void **pp)
{
    int rc;
    sqlite3_uint64 tStart, tElapse;
    VLogFile *p = (VLogFile *) pFile;
    tStart = vlog_time();
    rc = p->pReal->pMethods->xFetch(p->pReal, iOff, nAmt, pp);
    tElapse = vlog_time() - tStart;
    const char *result = pp ? "OK" : "Failed";
    vlogLogPrint(p->pLog, tStart, tElapse, VLOG_OP_FETCH, iOff, nAmt, result,
                 rc);
    return rc;
}