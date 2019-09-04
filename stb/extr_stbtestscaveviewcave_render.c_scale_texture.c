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
typedef  int uint32 ;

/* Variables and functions */
 int TEX_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int** texture ; 

void scale_texture(unsigned char *src, int x, int y, int w, int h)
{
   int i,j,k;
   assert(w == 256 && h == 256);
   for (j=0; j < TEX_SIZE; ++j) {
      for (i=0; i < TEX_SIZE; ++i) {
         uint32 val=0;
         for (k=0; k < 4; ++k) {
            val >>= 8;
            val += src[ 4*(x+(i>>2)) + 4*w*(y+(j>>2)) + k]<<24;
         }
         texture[j][i] = val;
      }
   }
}