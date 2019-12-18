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
typedef  int /*<<< orphan*/  UCollator ;
typedef  int UCollationResult ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
#define  UCOL_EQUAL 130 
#define  UCOL_GREATER 129 
#define  UCOL_LESS 128 
 int /*<<< orphan*/  assert (int) ; 
 int ucol_strcoll (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int icuCollationColl(
  void *pCtx,
  int nLeft,
  const void *zLeft,
  int nRight,
  const void *zRight
){
  UCollationResult res;
  UCollator *p = (UCollator *)pCtx;
  res = ucol_strcoll(p, (UChar *)zLeft, nLeft/2, (UChar *)zRight, nRight/2);
  switch( res ){
    case UCOL_LESS:    return -1;
    case UCOL_GREATER: return +1;
    case UCOL_EQUAL:   return 0;
  }
  assert(!"Unexpected return value from ucol_strcoll()");
  return 0;
}