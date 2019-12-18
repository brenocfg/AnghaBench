#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iInst; } ;
typedef  TYPE_1__ vtablog_vtab ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {double estimatedCost; int estimatedRows; } ;
typedef  TYPE_2__ sqlite3_index_info ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int vtablogBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  vtablog_vtab *pTab = (vtablog_vtab*)tab;
  printf("vtablogBestIndex(tab=%d):\n", pTab->iInst);
  pIdxInfo->estimatedCost = (double)500;
  pIdxInfo->estimatedRows = 500;
  return SQLITE_OK;
}