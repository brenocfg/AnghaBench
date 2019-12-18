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

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,char*) ; 
 char* sqlite3DbStrDup (int /*<<< orphan*/ *,char const*) ; 

void sqlite3SetString(char **pz, sqlite3 *db, const char *zNew){
  sqlite3DbFree(db, *pz);
  *pz = sqlite3DbStrDup(db, zNew);
}