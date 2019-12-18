#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_3__ {int /*<<< orphan*/  nJournal; int /*<<< orphan*/  nDatabase; } ;
typedef  TYPE_1__ fs_real_file ;
struct TYPE_4__ {scalar_t__ eType; TYPE_1__* pReal; } ;
typedef  TYPE_2__ fs_file ;

/* Variables and functions */
 scalar_t__ DATABASE_FILE ; 
 int SQLITE_OK ; 

__attribute__((used)) static int fsFileSize(sqlite3_file *pFile, sqlite_int64 *pSize){
  fs_file *p = (fs_file *)pFile;
  fs_real_file *pReal = p->pReal;
  if( p->eType==DATABASE_FILE ){
    *pSize = pReal->nDatabase;
  }else{
    *pSize = pReal->nJournal;
  }
  return SQLITE_OK;
}