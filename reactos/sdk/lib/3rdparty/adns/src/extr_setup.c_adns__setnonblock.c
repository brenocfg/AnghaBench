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
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  ADNS_SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

int adns__setnonblock(adns_state ads, ADNS_SOCKET fd) {
#ifdef ADNS_JGAA_WIN32
   unsigned long Val = 1;
   return (ioctlsocket (fd, FIONBIO, &Val) == 0) ? 0 : -1;
#else
  int r;

  r= fcntl(fd,F_GETFL,0); if (r<0) return errno;
  r |= O_NONBLOCK;
  r= fcntl(fd,F_SETFL,r); if (r<0) return errno;
  return 0;
#endif
}