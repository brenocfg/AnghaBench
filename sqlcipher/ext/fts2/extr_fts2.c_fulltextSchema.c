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

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,...) ; 

__attribute__((used)) static char *fulltextSchema(
  int nColumn,                  /* Number of columns */
  const char *const* azColumn,  /* List of columns */
  const char *zTableName        /* Name of the table */
){
  int i;
  char *zSchema, *zNext;
  const char *zSep = "(";
  zSchema = sqlite3_mprintf("CREATE TABLE x");
  for(i=0; i<nColumn; i++){
    zNext = sqlite3_mprintf("%s%s%Q", zSchema, zSep, azColumn[i]);
    sqlite3_free(zSchema);
    zSchema = zNext;
    zSep = ",";
  }
  zNext = sqlite3_mprintf("%s,%Q)", zSchema, zTableName);
  sqlite3_free(zSchema);
  return zNext;
}