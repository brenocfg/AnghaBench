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

__attribute__((used)) static int pointBeneathLine(
  double x0, double y0,
  double x1, double y1,
  double x2, double y2
){
  double y;
  if( x0==x1 && y0==y1 ) return 2;
  if( x1<x2 ){
    if( x0<=x1 || x0>x2 ) return 0;
  }else if( x1>x2 ){
    if( x0<=x2 || x0>x1 ) return 0;
  }else{
    /* Vertical line segment */
    if( x0!=x1 ) return 0;
    if( y0<y1 && y0<y2 ) return 0;
    if( y0>y1 && y0>y2 ) return 0;
    return 2;
  }
  y = y1 + (y2-y1)*(x0-x1)/(x2-x1);
  if( y0==y ) return 2;
  if( y0<y ) return 1;
  return 0;
}