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
 float* epf (char*,char*) ; 
 float* ldr_to_hdr (unsigned char*,int,int,int) ; 
 float* stbi_hdr_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_hdr_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_load_main (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

float *stbi_loadf_main(stbi *s, int *x, int *y, int *comp, int req_comp)
{
   unsigned char *data;
   #ifndef STBI_NO_HDR
   if (stbi_hdr_test(s))
      return stbi_hdr_load(s,x,y,comp,req_comp);
   #endif
   data = stbi_load_main(s, x, y, comp, req_comp);
   if (data)
      return ldr_to_hdr(data, *x, *y, req_comp ? req_comp : *comp);
   return epf("unknown image type", "Image not of any known type, or corrupt");
}