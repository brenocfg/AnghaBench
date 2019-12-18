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
 char* sqlite3_mprintf (char*,...) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vtablog_dequote (char*) ; 
 char* vtablog_parameter (char const*,int,char const*) ; 
 int /*<<< orphan*/  vtablog_trim_whitespace (char*) ; 

__attribute__((used)) static int vtablog_string_parameter(
  char **pzErr,            /* Leave the error message here, if there is one */
  const char *zParam,      /* Parameter we are checking for */
  const char *zArg,        /* Raw text of the virtual table argment */
  char **pzVal             /* Write the dequoted string value here */
){
  const char *zValue;
  zValue = vtablog_parameter(zParam,(int)strlen(zParam),zArg);
  if( zValue==0 ) return 0;
  if( *pzVal ){
    *pzErr = sqlite3_mprintf("more than one '%s' parameter", zParam);
    return 1;
  }
  *pzVal = sqlite3_mprintf("%s", zValue);
  if( *pzVal==0 ){
    *pzErr = sqlite3_mprintf("out of memory");
    return 1;
  }
  vtablog_trim_whitespace(*pzVal);
  vtablog_dequote(*pzVal);
  return 0;
}