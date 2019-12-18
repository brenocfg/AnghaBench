#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nDb; TYPE_2__* aDb; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_5__ {char* zDbSName; } ;
typedef  TYPE_2__ Db ;

/* Variables and functions */
 scalar_t__ sqlite3_stricmp (char*,char const*) ; 

int sqlite3FindDbName(sqlite3 *db, const char *zName){
  int i = -1;         /* Database number */
  if( zName ){
    Db *pDb;
    for(i=(db->nDb-1), pDb=&db->aDb[i]; i>=0; i--, pDb--){
      if( 0==sqlite3_stricmp(pDb->zDbSName, zName) ) break;
      /* "main" is always an acceptable alias for the primary database
      ** even if it has been renamed using SQLITE_DBCONFIG_MAINDBNAME. */
      if( i==0 && 0==sqlite3_stricmp("main", zName) ) break;
    }
  }
  return i;
}