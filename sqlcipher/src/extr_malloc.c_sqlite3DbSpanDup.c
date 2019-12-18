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
 scalar_t__ ALWAYS (int) ; 
 char* sqlite3DbStrNDup (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ sqlite3Isspace (char const) ; 

char *sqlite3DbSpanDup(sqlite3 *db, const char *zStart, const char *zEnd){
  int n;
  while( sqlite3Isspace(zStart[0]) ) zStart++;
  n = (int)(zEnd - zStart);
  while( ALWAYS(n>0) && sqlite3Isspace(zStart[n-1]) ) n--;
  return sqlite3DbStrNDup(db, zStart, n);
}