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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;

/* Variables and functions */
 scalar_t__ SQLITE_NULL ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zipfileTime () ; 

__attribute__((used)) static u32 zipfileGetTime(sqlite3_value *pVal){
  if( pVal==0 || sqlite3_value_type(pVal)==SQLITE_NULL ){
    return zipfileTime();
  }
  return (u32)sqlite3_value_int64(pVal);
}