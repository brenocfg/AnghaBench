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
 int orig_fallocate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsErrno (char*) ; 
 scalar_t__ tsIsFail () ; 

__attribute__((used)) static int ts_fallocate(int fd, off_t off, off_t len){
  if( tsIsFail() ){
    return tsErrno("fallocate");
  }
  return orig_fallocate(fd, off, len);
}