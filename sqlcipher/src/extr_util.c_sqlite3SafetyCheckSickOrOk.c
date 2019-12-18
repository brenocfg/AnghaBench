#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ magic; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_5__ {scalar_t__ xLog; } ;

/* Variables and functions */
 scalar_t__ SQLITE_MAGIC_BUSY ; 
 scalar_t__ SQLITE_MAGIC_OPEN ; 
 scalar_t__ SQLITE_MAGIC_SICK ; 
 int /*<<< orphan*/  logBadConnection (char*) ; 
 TYPE_3__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  testcase (int) ; 

int sqlite3SafetyCheckSickOrOk(sqlite3 *db){
  u32 magic;
  magic = db->magic;
  if( magic!=SQLITE_MAGIC_SICK &&
      magic!=SQLITE_MAGIC_OPEN &&
      magic!=SQLITE_MAGIC_BUSY ){
    testcase( sqlite3GlobalConfig.xLog!=0 );
    logBadConnection("invalid");
    return 0;
  }else{
    return 1;
  }
}