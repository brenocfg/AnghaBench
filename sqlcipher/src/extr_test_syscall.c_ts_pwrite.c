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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int orig_pwrite (int,void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ tsIsFailErrno (char*) ; 

__attribute__((used)) static int ts_pwrite(int fd, const void *aBuf, size_t nBuf, off_t off){
  if( tsIsFailErrno("pwrite") ){
    return -1;
  }
  return orig_pwrite(fd, aBuf, nBuf, off);
}