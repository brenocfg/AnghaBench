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
struct TYPE_3__ {int /*<<< orphan*/  idxFlags; } ;
typedef  TYPE_1__ sqlite3_index_info ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_INDEX_SCAN_UNIQUE ; 
 int sqlite3_libversion_number () ; 

__attribute__((used)) static void fts5SetUniqueFlag(sqlite3_index_info *pIdxInfo){
#if SQLITE_VERSION_NUMBER>=3008012
#ifndef SQLITE_CORE
  if( sqlite3_libversion_number()>=3008012 )
#endif
  {
    pIdxInfo->idxFlags |= SQLITE_INDEX_SCAN_UNIQUE;
  }
#endif
}