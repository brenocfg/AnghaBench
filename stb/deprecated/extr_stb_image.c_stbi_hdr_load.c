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

/* Variables and functions */
 float* hdr_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

__attribute__((used)) static float *stbi_hdr_load(stbi *s, int *x, int *y, int *comp, int req_comp)
{
   return hdr_load(s,x,y,comp,req_comp);
}