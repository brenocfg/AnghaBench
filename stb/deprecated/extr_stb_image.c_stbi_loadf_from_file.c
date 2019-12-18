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
typedef  int /*<<< orphan*/  stbi ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  start_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float* stbi_loadf_main (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

float *stbi_loadf_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
   stbi s;
   start_file(&s,f);
   return stbi_loadf_main(&s,x,y,comp,req_comp);
}