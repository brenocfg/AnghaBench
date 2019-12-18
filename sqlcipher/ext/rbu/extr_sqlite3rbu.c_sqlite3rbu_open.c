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
typedef  int /*<<< orphan*/  sqlite3rbu ;

/* Variables and functions */
 int /*<<< orphan*/ * openRbuHandle (char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * rbuMisuseError () ; 

sqlite3rbu *sqlite3rbu_open(
  const char *zTarget, 
  const char *zRbu,
  const char *zState
){
  if( zTarget==0 || zRbu==0 ){ return rbuMisuseError(); }
  /* TODO: Check that zTarget and zRbu are non-NULL */
  return openRbuHandle(zTarget, zRbu, zState);
}