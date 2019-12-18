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
struct TYPE_3__ {scalar_t__ rc; } ;
typedef  TYPE_1__ Error ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 double currentTime () ; 
 double timelimit ; 

__attribute__((used)) static int timetostop_x(
  Error *pErr                     /* IN/OUT: Error code */
){
  int ret = 1;
  if( pErr->rc==SQLITE_OK ){
    double t = currentTime();
    ret = (t >= timelimit);
  }
  return ret;
}