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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int SQLITE_INTEGER ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int sqlite3_value_numeric_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite3_int64 fts3DocidRange(sqlite3_value *pVal, i64 iDefault){
  if( pVal ){
    int eType = sqlite3_value_numeric_type(pVal);
    if( eType==SQLITE_INTEGER ){
      return sqlite3_value_int64(pVal);
    }
  }
  return iDefault;
}