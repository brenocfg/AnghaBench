#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int iTrace; scalar_t__ iTimeout; scalar_t__ bIgnoreSqlErrors; } ;

/* Variables and functions */
 int SQLITE_BUSY ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOTICE ; 
 int SQLITE_SCHEMA ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  errorMessage (char*,int,char const*) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  logMessage (char*,char const*) ; 

__attribute__((used)) static void sqlErrorCallback(void *pArg, int iErrCode, const char *zMsg){
  UNUSED_PARAMETER(pArg);
  if( iErrCode==SQLITE_ERROR && g.bIgnoreSqlErrors ) return;
  if( (iErrCode&0xff)==SQLITE_SCHEMA && g.iTrace<3 ) return;
  if( g.iTimeout==0 && (iErrCode&0xff)==SQLITE_BUSY && g.iTrace<3 ) return;
  if( (iErrCode&0xff)==SQLITE_NOTICE ){
    logMessage("(info) %s", zMsg);
  }else{
    errorMessage("(errcode=%d) %s", iErrCode, zMsg);
  }
}