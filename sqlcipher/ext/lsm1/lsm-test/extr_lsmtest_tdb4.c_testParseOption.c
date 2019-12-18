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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int testParseOption(
  const char **pzIn,              /* IN/OUT: pointer to next option */
  const char **pzOpt,             /* OUT: nul-terminated option name */
  const char **pzArg,             /* OUT: nul-terminated option argument */
  char *pSpace                    /* Temporary space for output params */
){
  const char *p = *pzIn;
  const char *pStart;
  int n;

  char *pOut = pSpace;

  while( *p==' ' ) p++;
  pStart = p;
  while( *p && *p!='=' ) p++;
  if( *p==0 ) return 1;

  n = (p - pStart);
  memcpy(pOut, pStart, n);
  *pzOpt = pOut;
  pOut += n;
  *pOut++ = '\0';

  p++;
  pStart = p;
  while( *p && *p!=' ' ) p++;
  n = (p - pStart);

  memcpy(pOut, pStart, n);
  *pzArg = pOut;
  pOut += n;
  *pOut++ = '\0';

  *pzIn = p;
  return 0;
}