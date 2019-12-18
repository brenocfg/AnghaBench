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
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idxDatabaseError(
  sqlite3 *db,                    /* Database handle */
  char **pzErrmsg                 /* Write error here */
){
  *pzErrmsg = sqlite3_mprintf("%s", sqlite3_errmsg(db));
}