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
typedef  int /*<<< orphan*/  CmdLineOption ;

/* Variables and functions */
 int /*<<< orphan*/  option_requires_argument_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_integer_option(CmdLineOption *pOpt, const char *zArg){
  int i = 0;
  int iRet = 0;
  int bSign = 1;
  if( zArg[0]=='-' ){
    bSign = -1;
    i = 1;
  }
  while( zArg[i] ){
    if( zArg[i]<'0' || zArg[i]>'9' ) option_requires_argument_error(pOpt);
    iRet = iRet*10 + (zArg[i] - '0');
    i++;
  }
  return (iRet*bSign);
}