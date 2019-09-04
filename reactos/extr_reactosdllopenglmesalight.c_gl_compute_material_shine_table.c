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
struct gl_material {float* ShineTable; } ;

/* Variables and functions */
 int SHINE_TABLE_SIZE ; 

void gl_compute_material_shine_table( struct gl_material *m )
{
   int i;

   m->ShineTable[0] = 0.0F;
   for (i=1;i<SHINE_TABLE_SIZE;i++) {
#if 0
      double x = pow( i/(double)(SHINE_TABLE_SIZE-1), exponent );
      if (x<1.0e-10) {
         m->ShineTable[i] = 0.0F;
      }
      else {
         m->ShineTable[i] = x;
      }
#else
      /* just invalidate the table */
      m->ShineTable[i] = -1.0;
#endif
   }
}