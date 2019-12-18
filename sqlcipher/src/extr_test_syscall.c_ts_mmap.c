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
 void* MAP_FAILED ; 
 void* orig_mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ tsIsFailErrno (char*) ; 

__attribute__((used)) static void *ts_mmap(
  void *pAddr, 
  size_t nByte, 
  int prot, 
  int flags, 
  int fd, 
  off_t iOff
){
  if( tsIsFailErrno("mmap") ){
    return MAP_FAILED;
  }
  return orig_mmap(pAddr, nByte, prot, flags, fd, iOff);
}