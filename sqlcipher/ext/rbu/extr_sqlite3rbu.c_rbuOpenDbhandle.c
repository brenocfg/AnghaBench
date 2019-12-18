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
struct TYPE_3__ {scalar_t__ rc; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  zVfsName; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_URI ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_open_v2 (char const*,int /*<<< orphan*/ **,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sqlite3 *rbuOpenDbhandle(
  sqlite3rbu *p, 
  const char *zName, 
  int bUseVfs
){
  sqlite3 *db = 0;
  if( p->rc==SQLITE_OK ){
    const int flags = SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_URI;
    p->rc = sqlite3_open_v2(zName, &db, flags, bUseVfs ? p->zVfsName : 0);
    if( p->rc ){
      p->zErrmsg = sqlite3_mprintf("%s", sqlite3_errmsg(db));
      sqlite3_close(db);
      db = 0;
    }
  }
  return db;
}