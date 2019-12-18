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
typedef  int /*<<< orphan*/  sqlite3_int64 ;

/* Variables and functions */
 scalar_t__ sqlite3DecOrHexToI64 (char const*,int /*<<< orphan*/ *) ; 
 char* sqlite3_uri_parameter (char const*,char const*) ; 

sqlite3_int64 sqlite3_uri_int64(
  const char *zFilename,    /* Filename as passed to xOpen */
  const char *zParam,       /* URI parameter sought */
  sqlite3_int64 bDflt       /* return if parameter is missing */
){
  const char *z = sqlite3_uri_parameter(zFilename, zParam);
  sqlite3_int64 v;
  if( z && sqlite3DecOrHexToI64(z, &v)==0 ){
    bDflt = v;
  }
  return bDflt;
}