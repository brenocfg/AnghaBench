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
typedef  int /*<<< orphan*/  z3 ;
typedef  int /*<<< orphan*/  z2 ;
typedef  int /*<<< orphan*/  z1 ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {scalar_t__ zFilename; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ VLogLog ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,...) ; 

__attribute__((used)) static void vlogLogPrint(
  VLogLog *pLog,                 /* The log file to write into */
  sqlite3_int64 tStart,            /* Start time of system call */
  sqlite3_int64 tElapse,           /* Elapse time of system call */
  const char *zOp,                 /* Type of system call */
  sqlite3_int64 iArg1,             /* First argument */
  sqlite3_int64 iArg2,             /* Second argument */
  const char *zArg3,               /* Third argument */
  int iRes                         /* Result */
){
  char z1[40], z2[40], z3[2000];
  if( pLog==0 ) return;
  if( iArg1>=0 ){
    sqlite3_snprintf(sizeof(z1), z1, "%lld", iArg1);
  }else{
    z1[0] = 0;
  }
  if( iArg2>=0 ){
    sqlite3_snprintf(sizeof(z2), z2, "%lld", iArg2);
  }else{
    z2[0] = 0;
  }
  if( zArg3 ){
    sqlite3_snprintf(sizeof(z3), z3, "\"%.*w\"", sizeof(z3)-4, zArg3);
  }else{
    z3[0] = 0;
  }
  fprintf(pLog->out,"%lld,%lld,%s,%d,%s,%s,%s,%d\n",
      tStart, tElapse, zOp, pLog->zFilename==0, z1, z2, z3, iRes);
}