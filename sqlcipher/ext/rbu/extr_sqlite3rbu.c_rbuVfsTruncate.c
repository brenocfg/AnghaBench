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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_6__ {int openFlags; TYPE_3__* pReal; scalar_t__ pRbu; } ;
typedef  TYPE_2__ rbu_file ;
struct TYPE_7__ {TYPE_1__* pMethods; } ;
struct TYPE_5__ {int (* xTruncate ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int rbuUpdateTempSize (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbuVfsTruncate(sqlite3_file *pFile, sqlite_int64 size){
  rbu_file *p = (rbu_file*)pFile;
  if( (p->openFlags & SQLITE_OPEN_DELETEONCLOSE) && p->pRbu ){
    int rc = rbuUpdateTempSize(p, size);
    if( rc!=SQLITE_OK ) return rc;
  }
  return p->pReal->pMethods->xTruncate(p->pReal, size);
}