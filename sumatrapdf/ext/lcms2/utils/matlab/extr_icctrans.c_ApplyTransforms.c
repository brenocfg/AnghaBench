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
typedef  int /*<<< orphan*/  const mxArray ;

/* Variables and functions */
 size_t GetNumberOfPixels (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,double*,double*,size_t) ; 
 int /*<<< orphan*/  hColorTransform ; 
 double* mxGetPr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static
void ApplyTransforms(const mxArray *In, mxArray *Out)
{   
	double *Input  = mxGetPr(In); 
	double *Output = mxGetPr(Out);    
	size_t nPixels = GetNumberOfPixels(In);;

	cmsDoTransform(hColorTransform, Input, Output, nPixels );

}