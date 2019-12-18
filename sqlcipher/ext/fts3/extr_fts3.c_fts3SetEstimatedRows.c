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
struct TYPE_3__ {int /*<<< orphan*/  estimatedRows; } ;
typedef  TYPE_1__ sqlite3_index_info ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int sqlite3_libversion_number () ; 

__attribute__((used)) static void fts3SetEstimatedRows(sqlite3_index_info *pIdxInfo, i64 nRow){
#if SQLITE_VERSION_NUMBER>=3008002
  if( sqlite3_libversion_number()>=3008002 ){
    pIdxInfo->estimatedRows = nRow;
  }
#endif
}