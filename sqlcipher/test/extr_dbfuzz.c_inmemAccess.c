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
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  VFile ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/ * findVFile (char const*) ; 

__attribute__((used)) static int inmemAccess(
  sqlite3_vfs *pVfs,
  const char *zFilename,
  int flags,
  int *pResOut
){
  VFile *pVFile = findVFile(zFilename);
  *pResOut =  pVFile!=0;
  return SQLITE_OK;
}