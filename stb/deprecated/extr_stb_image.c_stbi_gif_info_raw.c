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
struct TYPE_3__ {int w; int h; } ;
typedef  TYPE_1__ stbi_gif ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int /*<<< orphan*/  stbi_gif_header (int /*<<< orphan*/ *,TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi_gif_info_raw(stbi *s, int *x, int *y, int *comp)
{
   stbi_gif g;   
   if (!stbi_gif_header(s, &g, comp, 1)) {
      stbi_rewind( s );
      return 0;
   }
   if (x) *x = g.w;
   if (y) *y = g.h;
   return 1;
}