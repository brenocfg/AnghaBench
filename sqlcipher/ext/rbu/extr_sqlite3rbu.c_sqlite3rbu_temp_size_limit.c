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
struct TYPE_3__ {scalar_t__ szTempLimit; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */

sqlite3_int64 sqlite3rbu_temp_size_limit(sqlite3rbu *pRbu, sqlite3_int64 n){
  if( n>=0 ){
    pRbu->szTempLimit = n;
  }
  return pRbu->szTempLimit;
}