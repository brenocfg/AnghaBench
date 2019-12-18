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
 int False ; 
 int True ; 
 int clip_endx ; 
 int clip_endy ; 
 int clip_startx ; 
 int clip_starty ; 

int warp_coords(int* x, int* y, int* cx, int* cy, int* srcx, int* srcy)
{
  int dx;
  int dy;
//  int lx = *x, ly = *y, lcx = *cx, lcy = *cy;

  if (clip_startx > *x)
    dx = clip_startx - *x;
  else
    dx = 0;
  if (clip_starty > *y)
    dy = clip_starty - *y;
  else
    dy = 0;
  if (*x + *cx > clip_endx)
    *cx = (*cx - ((*x + *cx) - clip_endx)) /*+ 1*/;
  if (*y + *cy > clip_endy)
    *cy = (*cy - ((*y + *cy) - clip_endy)) /*+ 1*/;
  *cx = *cx - dx;
  *cy = *cy - dy;
  if (*cx <= 0)
    return False;
  if (*cy <= 0)
    return False;
  *x = *x + dx;
  *y = *y + dy;
  if (srcx != NULL)
    *srcx = *srcx + dx;
  if (srcy != NULL)
    *srcy = *srcy + dy;

//  if (*x != lx || *y != ly || *cx != lcx || *cy != lcy)
//    printf("%d %d %d %d to %d %d %d %d\n", lx, ly, lcx, lcy, *x, *y, *cx, *cy);

  return True;
}