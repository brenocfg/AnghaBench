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
typedef  int /*<<< orphan*/  stbi ;
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ png ;

/* Variables and functions */
 unsigned char* do_png (TYPE_1__*,int*,int*,int*,int) ; 

__attribute__((used)) static unsigned char *stbi_png_load(stbi *s, int *x, int *y, int *comp, int req_comp)
{
   png p;
   p.s = s;
   return do_png(&p, x,y,comp,req_comp);
}