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
typedef  int /*<<< orphan*/  Str ;

/* Variables and functions */
 int /*<<< orphan*/  strPrintf (int /*<<< orphan*/ *,char const*,char const*,...) ; 

__attribute__((used)) static void strPrintfArray(
  Str *pStr,                      /* String object to append to */
  const char *zSep,               /* Separator string */
  const char *zFmt,               /* Format for each entry */
  char **az, int n                /* Array of strings & its size (or -1) */
){
  int i;
  for(i=0; az[i] && (i<n || n<0); i++){
    if( i!=0 ) strPrintf(pStr, "%s", zSep);
    strPrintf(pStr, zFmt, az[i], az[i], az[i]);
  }
}