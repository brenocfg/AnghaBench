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
typedef  int /*<<< orphan*/  stbi_io_callbacks ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int /*<<< orphan*/  start_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 unsigned char* stbi_load_main (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

unsigned char *stbi_load_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp)
{
   stbi s;
   start_callbacks(&s, (stbi_io_callbacks *) clbk, user);
   return stbi_load_main(&s,x,y,comp,req_comp);
}