#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {int /*<<< orphan*/  sz; } ;
typedef  TYPE_1__ MemFile ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int memFileSize(sqlite3_file *pFile, sqlite_int64 *pSize){
  MemFile *p = (MemFile *)pFile;
  *pSize = p->sz;
  return SQLITE_OK;
}