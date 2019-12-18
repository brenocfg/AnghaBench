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
typedef  int sqlite3_int64 ;
struct TYPE_5__ {TYPE_1__* pFile; } ;
typedef  TYPE_2__ quota_FILE ;
struct TYPE_4__ {int iSize; } ;

/* Variables and functions */

sqlite3_int64 sqlite3_quota_file_size(quota_FILE *p){
  return p->pFile ? p->pFile->iSize : -1;
}