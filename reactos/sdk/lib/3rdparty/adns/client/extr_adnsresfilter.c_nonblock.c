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

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int nonblock(int fd, int isnonblock) {
  int r;

  r= fcntl(fd,F_GETFL);
  if (r==-1) return -1;
  r= fcntl(fd,F_SETFL, isnonblock ? r|O_NONBLOCK : r&~O_NONBLOCK);
  if (r==-1) return -1;
  return 0;
}