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
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/ * openRbuHandle (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/ * rbuMisuseError () ; 
 int strlen (char const*) ; 

sqlite3rbu *sqlite3rbu_vacuum(
  const char *zTarget, 
  const char *zState
){
  if( zTarget==0 ){ return rbuMisuseError(); }
  if( zState ){
    int n = strlen(zState);
    if( n>=7 && 0==memcmp("-vactmp", &zState[n-7], 7) ){
      return rbuMisuseError();
    }
  }
  /* TODO: Check that both arguments are non-NULL */
  return openRbuHandle(0, zTarget, zState);
}