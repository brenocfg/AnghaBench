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

/* Variables and functions */
 int /*<<< orphan*/  SW ; 
 int /*<<< orphan*/  mexPrintf (char*,...) ; 

__attribute__((used)) static
void PrintHelp(void)
{
	mexPrintf("(MX) little cms ColorSpace conversion tool - v2.0\n\n");

	mexPrintf("usage: icctrans (mVar, flags)\n\n");

	mexPrintf("mVar : Matlab array.\n");
	mexPrintf("flags: a string containing one or more of following options.\n\n");
	mexPrintf("\t%cv - Verbose\n", SW);
	mexPrintf("\t%ci<profile> - Input profile (defaults to sRGB)\n", SW);
	mexPrintf("\t%co<profile> - Output profile (defaults to sRGB)\n", SW);   
	mexPrintf("\t%cl<profile> - Transform by device-link profile\n", SW);      
	mexPrintf("\t%cm<profiles> - Apply multiprofile chain\n", SW);      

	mexPrintf("\t%ct<n> - Rendering intent\n", SW);    

	mexPrintf("\t%cb - Black point compensation\n", SW);
	mexPrintf("\t%cc<0,1,2,3> - Optimize transform (0=Off, 1=Normal, 2=Hi-res, 3=Lo-Res) [defaults to 1]\n", SW);     

	mexPrintf("\t%cp<profile> - Soft proof profile\n", SW);
	mexPrintf("\t%cr<0,1,2,3> - Soft proof intent\n", SW);

	mexPrintf("\nYou can use following built-ins as profiles:\n\n");

	mexPrintf("\t*Lab2  -- D50-based v2 CIEL*a*b\n"
	"\t*Lab4  -- D50-based v4 CIEL*a*b\n"
	"\t*Lab   -- D50-based v4 CIEL*a*b\n"
	"\t*XYZ   -- CIE XYZ (PCS)\n"
	"\t*sRGB  -- IEC6 1996-2.1 sRGB color space\n" 
	"\t*Gray22 - Monochrome of Gamma 2.2\n"
	"\t*Gray30 - Monochrome of Gamma 3.0\n"
	"\t*null   - Monochrome black for all input\n"
	"\t*Lin2222- CMYK linearization of gamma 2.2 on each channel\n\n");

	mexPrintf("For suggestions, comments, bug reports etc. send mail to info@littlecms.com\n\n");

}