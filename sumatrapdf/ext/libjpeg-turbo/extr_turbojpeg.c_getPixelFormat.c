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
 int TJPF_BGR ; 
 int TJPF_BGRX ; 
 int TJPF_GRAY ; 
 int TJPF_RGB ; 
 int TJPF_RGBX ; 
 int TJPF_XBGR ; 
 int TJPF_XRGB ; 
 int TJ_ALPHAFIRST ; 
 int TJ_BGR ; 

__attribute__((used)) static int getPixelFormat(int pixelSize, int flags)
{
	if(pixelSize==1) return TJPF_GRAY;
	if(pixelSize==3)
	{
		if(flags&TJ_BGR) return TJPF_BGR;
		else return TJPF_RGB;
	}
	if(pixelSize==4)
	{
		if(flags&TJ_ALPHAFIRST)
		{
			if(flags&TJ_BGR) return TJPF_XBGR;
			else return TJPF_XRGB;
		}
		else
		{
			if(flags&TJ_BGR) return TJPF_BGRX;
			else return TJPF_RGBX;
		}
	}
	return -1;
}