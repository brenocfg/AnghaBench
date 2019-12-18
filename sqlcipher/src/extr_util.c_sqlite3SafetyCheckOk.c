#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ magic; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_6__ {scalar_t__ xLog; } ;

/* Variables and functions */
 scalar_t__ SQLITE_MAGIC_OPEN ; 
 int /*<<< orphan*/  logBadConnection (char*) ; 
 TYPE_4__ sqlite3GlobalConfig ; 
 scalar_t__ sqlite3SafetyCheckSickOrOk (TYPE_1__*) ; 
 int /*<<< orphan*/  testcase (int) ; 

int sqlite3SafetyCheckOk(sqlite3 *db){
  u32 magic;
  if( db==0 ){
    logBadConnection("NULL");
    return 0;
  }
  magic = db->magic;
  if( magic!=SQLITE_MAGIC_OPEN ){
    if( sqlite3SafetyCheckSickOrOk(db) ){
      testcase( sqlite3GlobalConfig.xLog!=0 );
      logBadConnection("unopened");
    }
    return 0;
  }else{
    return 1;
  }
}