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
struct stat {int st_size; } ;
typedef  int i64 ;
struct TYPE_3__ {scalar_t__ rc; } ;
typedef  TYPE_1__ Error ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static i64 filesize_x(
  Error *pErr,
  const char *zFile
){
  i64 iRet = 0;
  if( pErr->rc==SQLITE_OK ){
    struct stat sStat;
    if( stat(zFile, &sStat) ){
      iRet = -1;
    }else{
      iRet = sStat.st_size;
    }
  }
  return iRet;
}