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
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int MAX_SECTOR_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3OsSectorSize (int /*<<< orphan*/ *) ; 

int sqlite3SectorSize(sqlite3_file *pFile){
  int iRet = sqlite3OsSectorSize(pFile);
  if( iRet<32 ){
    iRet = 512;
  }else if( iRet>MAX_SECTOR_SIZE ){
    assert( MAX_SECTOR_SIZE>=512 );
    iRet = MAX_SECTOR_SIZE;
  }
  return iRet;
}