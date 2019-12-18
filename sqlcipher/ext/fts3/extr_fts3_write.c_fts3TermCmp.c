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
 int MIN (int,int) ; 
 int memcmp (char const*,char const*,int) ; 

__attribute__((used)) static int fts3TermCmp(
  const char *zLhs, int nLhs,     /* LHS of comparison */
  const char *zRhs, int nRhs      /* RHS of comparison */
){
  int nCmp = MIN(nLhs, nRhs);
  int res;

  res = memcmp(zLhs, zRhs, nCmp);
  if( res==0 ) res = nLhs - nRhs;

  return res;
}