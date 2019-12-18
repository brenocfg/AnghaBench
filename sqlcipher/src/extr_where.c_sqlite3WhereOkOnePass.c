#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ eOnePass; int /*<<< orphan*/  aiCurOnePass; } ;
typedef  TYPE_1__ WhereInfo ;

/* Variables and functions */
 scalar_t__ ONEPASS_OFF ; 
 scalar_t__ ONEPASS_SINGLE ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DebugPrintf (char*,char*,int,int) ; 
 scalar_t__ sqlite3WhereTrace ; 

int sqlite3WhereOkOnePass(WhereInfo *pWInfo, int *aiCur){
  memcpy(aiCur, pWInfo->aiCurOnePass, sizeof(int)*2);
#ifdef WHERETRACE_ENABLED
  if( sqlite3WhereTrace && pWInfo->eOnePass!=ONEPASS_OFF ){
    sqlite3DebugPrintf("%s cursors: %d %d\n",
         pWInfo->eOnePass==ONEPASS_SINGLE ? "ONEPASS_SINGLE" : "ONEPASS_MULTI",
         aiCur[0], aiCur[1]);
  }
#endif
  return pWInfo->eOnePass;
}