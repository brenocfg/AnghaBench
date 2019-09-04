#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ img_buffer; scalar_t__ img_buffer_end; } ;
typedef  TYPE_1__ stbi ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 unsigned char* stbi_load_main (TYPE_1__*,int*,int*,int*,int) ; 

unsigned char *stbi_load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
   unsigned char *result;
   stbi s;
   start_file(&s,f);
   result = stbi_load_main(&s,x,y,comp,req_comp);
   if (result) {
      // need to 'unget' all the characters in the IO buffer
      fseek(f, - (int) (s.img_buffer_end - s.img_buffer), SEEK_CUR);
   }
   return result;
}