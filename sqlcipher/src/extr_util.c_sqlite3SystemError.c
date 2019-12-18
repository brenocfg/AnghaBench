#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pVfs; int /*<<< orphan*/  iSysErrno; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int SQLITE_CANTOPEN ; 
 int SQLITE_IOERR ; 
 int SQLITE_IOERR_NOMEM ; 
 int /*<<< orphan*/  sqlite3OsGetLastError (int /*<<< orphan*/ ) ; 

void sqlite3SystemError(sqlite3 *db, int rc){
  if( rc==SQLITE_IOERR_NOMEM ) return;
  rc &= 0xff;
  if( rc==SQLITE_CANTOPEN || rc==SQLITE_IOERR ){
    db->iSysErrno = sqlite3OsGetLastError(db->pVfs);
  }
}