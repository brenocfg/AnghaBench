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
struct TYPE_3__ {int dx; int y; int len; } ;
typedef  TYPE_1__ segment ;

/* Variables and functions */
 int LEN_LIMIT ; 
 int X_LIMIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int* last_x ; 
 int non_empty ; 
 int /*<<< orphan*/ * num_seg ; 
 int /*<<< orphan*/  segments ; 
 int /*<<< orphan*/  stb_arr_push (int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  vsegments ; 

void add_seg(int x, int y, int len, int horizontal)
{
   segment s;

   while (x - last_x[horizontal] > X_LIMIT) {
      add_seg(last_x[horizontal] + X_LIMIT, 0, 0, horizontal);
   }
   while (len > LEN_LIMIT) {
      add_seg(x, y, LEN_LIMIT, horizontal);
      len -= LEN_LIMIT;
      x += LEN_LIMIT*horizontal;
      y += LEN_LIMIT*!horizontal;
   }

   s.dx = x - last_x[horizontal];
   s.y = y;
   s.len = len;
   non_empty += len != 0;
   //assert(s.x == x);
   assert(s.y == y);
   assert(s.len == len);
   ++num_seg[horizontal];
   if (horizontal)
      stb_arr_push(segments, s);
   else
      stb_arr_push(vsegments, s);
   last_x[horizontal] = x;
}