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
typedef  float stbi_uc ;

/* Variables and functions */
 float* epf (char*,char*) ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  l2h_gamma ; 
 float l2h_scale ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pow (float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float   *ldr_to_hdr(stbi_uc *data, int x, int y, int comp)
{
   int i,k,n;
   float *output = (float *) malloc(x * y * comp * sizeof(float));
   if (output == NULL) { free(data); return epf("outofmem", "Out of memory"); }
   // compute number of non-alpha components
   if (comp & 1) n = comp; else n = comp-1;
   for (i=0; i < x*y; ++i) {
      for (k=0; k < n; ++k) {
         output[i*comp + k] = (float) pow(data[i*comp+k]/255.0f, l2h_gamma) * l2h_scale;
      }
      if (k < comp) output[i*comp + k] = data[i*comp+k]/255.0f;
   }
   free(data);
   return output;
}