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
struct pixel_buffer {double* lambda; int /*<<< orphan*/  primitive; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BITMAP ; 
 int PB_SIZE ; 
 scalar_t__ calloc (int,int) ; 

struct pixel_buffer *gl_alloc_pb(void)
{
   struct pixel_buffer *pb;
   pb = (struct pixel_buffer *) calloc(sizeof(struct pixel_buffer), 1);
   if (pb) {
      int i;
      /* set non-zero fields */
      pb->primitive = GL_BITMAP;
      /* Set all lambda values to 0.0 since we don't do mipmapping for
       * points or lines and want to use the level 0 texture image.
       */
      for (i=0; i<PB_SIZE; i++) {
         pb->lambda[i] = 0.0;
      }
   }
   return pb;
}