#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  TYPE_1__* adns_state ;
struct TYPE_5__ {int /*<<< orphan*/  tcpw; int /*<<< orphan*/  udpw; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_events (TYPE_1__*,int,struct timeval**,struct timeval*,struct timeval) ; 
 int /*<<< orphan*/  timeouts_queue (TYPE_1__*,int,struct timeval**,struct timeval*,struct timeval,int /*<<< orphan*/ *) ; 

void adns__timeouts(adns_state ads, int act,
		    struct timeval **tv_io, struct timeval *tvbuf,
		    struct timeval now) {
  timeouts_queue(ads,act,tv_io,tvbuf,now, &ads->udpw);
  timeouts_queue(ads,act,tv_io,tvbuf,now, &ads->tcpw);
  tcp_events(ads,act,tv_io,tvbuf,now);
}