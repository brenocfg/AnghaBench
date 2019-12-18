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
typedef  int /*<<< orphan*/  sqlite3_uint64 ;

/* Variables and functions */
 int orig_pread64 (int,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ tsIsFailErrno (char*) ; 

__attribute__((used)) static int ts_pread64(int fd, void *aBuf, size_t nBuf, sqlite3_uint64 off){
  if( tsIsFailErrno("pread64") ){
    return -1;
  }
  return orig_pread64(fd, aBuf, nBuf, off);
}