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
 int /*<<< orphan*/ * minecraft_geom_for_blocktype ; 
 unsigned char** minecraft_tex1_for_blocktype ; 
 size_t next_blocktype ; 

void build_wood_variations(int bt, unsigned char *map)
{
   int i,k;
   unsigned char tex[4] = { 5, 198, 214, 199 };
   for (i=0; i < 4; ++i) {
      if (i == 0)
         map[i] = bt;
      else {
         map[i] = next_blocktype;
         for (k=0; k < 6; ++k) {
            minecraft_tex1_for_blocktype[next_blocktype][k] = tex[i];
         }
         minecraft_geom_for_blocktype[next_blocktype] = minecraft_geom_for_blocktype[bt];
         --next_blocktype;
      }
   }
   map[i] = map[i-1];
   ++i;
   for (; i < 16; ++i)
      map[i] = bt;
}