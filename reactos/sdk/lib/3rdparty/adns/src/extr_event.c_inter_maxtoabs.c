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
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct TYPE_3__ {int quot; } ;
typedef  TYPE_1__ ldiv_t ;

/* Variables and functions */
 int /*<<< orphan*/  inter_maxto (struct timeval**,struct timeval*,struct timeval) ; 
 TYPE_1__ ldiv (int,int) ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 

__attribute__((used)) static void inter_maxtoabs(struct timeval **tv_io, struct timeval *tvbuf,
			   struct timeval now, struct timeval maxtime) {
  /* tv_io may be 0 */
  ldiv_t dr;

/*fprintf(stderr,"inter_maxtoabs now=%ld.%06ld maxtime=%ld.%06ld\n",
	now.tv_sec,now.tv_usec,maxtime.tv_sec,maxtime.tv_usec);*/
  if (!tv_io) return;
  maxtime.tv_sec -= (now.tv_sec+2);
  maxtime.tv_usec -= (now.tv_usec-2000000);
  dr= ldiv(maxtime.tv_usec,1000000);
  maxtime.tv_sec += dr.quot;
  maxtime.tv_usec -= dr.quot*1000000;
  if (maxtime.tv_sec<0) timerclear(&maxtime);
  inter_maxto(tv_io,tvbuf,maxtime);
}