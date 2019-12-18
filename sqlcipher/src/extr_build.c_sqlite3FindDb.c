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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,char*) ; 
 int sqlite3FindDbName (int /*<<< orphan*/ *,char*) ; 
 char* sqlite3NameFromToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sqlite3FindDb(sqlite3 *db, Token *pName){
  int i;                               /* Database number */
  char *zName;                         /* Name we are searching for */
  zName = sqlite3NameFromToken(db, pName);
  i = sqlite3FindDbName(db, zName);
  sqlite3DbFree(db, zName);
  return i;
}