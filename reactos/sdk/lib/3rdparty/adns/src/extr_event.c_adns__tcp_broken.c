#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* adns_state ;
typedef  TYPE_3__* adns_query ;
struct TYPE_9__ {int /*<<< orphan*/  retries; struct TYPE_9__* next; } ;
struct TYPE_7__ {TYPE_3__* head; } ;
struct TYPE_8__ {scalar_t__ tcpstate; int tcpserver; int nservers; TYPE_1__ tcpw; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns__warn (TYPE_2__*,int,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ server_broken ; 
 scalar_t__ server_connecting ; 
 scalar_t__ server_ok ; 
 int /*<<< orphan*/  tcp_close (TYPE_2__*) ; 

void adns__tcp_broken(adns_state ads, const char *what, const char *why) {
  int serv;
  adns_query qu;

  assert(ads->tcpstate == server_connecting || ads->tcpstate == server_ok);
  serv= ads->tcpserver;
  if (what) adns__warn(ads,serv,0,"TCP connection failed: %s: %s",what,why);

  if (ads->tcpstate == server_connecting) {
    /* Counts as a retry for all the queries waiting for TCP. */
    for (qu= ads->tcpw.head; qu; qu= qu->next)
      qu->retries++;
  }

  tcp_close(ads);
  ads->tcpstate= server_broken;
  ads->tcpserver= (serv+1)%ads->nservers;
}