#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int stbi__uint8 ;
typedef  scalar_t__ stbi__uint32 ;
struct TYPE_4__ {scalar_t__ img_x; scalar_t__ img_y; } ;
typedef  TYPE_1__ stbi ;
struct TYPE_5__ {int* out; TYPE_1__* s; } ;
typedef  TYPE_2__ png ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int compute_transparency(png *z, stbi__uint8 tc[3], int out_n)
{
   stbi *s = z->s;
   stbi__uint32 i, pixel_count = s->img_x * s->img_y;
   stbi__uint8 *p = z->out;

   // compute color-based transparency, assuming we've
   // already got 255 as the alpha value in the output
   assert(out_n == 2 || out_n == 4);

   if (out_n == 2) {
      for (i=0; i < pixel_count; ++i) {
         p[1] = (p[0] == tc[0] ? 0 : 255);
         p += 2;
      }
   } else {
      for (i=0; i < pixel_count; ++i) {
         if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2])
            p[3] = 0;
         p += 4;
      }
   }
   return 1;
}