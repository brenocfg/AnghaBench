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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;

/* Variables and functions */
 int BYTES_SH (int) ; 
 int CHANNELS_SH (int) ; 
 int COLORSPACE_SH (int /*<<< orphan*/ ) ; 
 int FLOAT_SH (int) ; 
 int PLANAR_SH (int) ; 
 int /*<<< orphan*/  _cmsLCMScolorSpace (int /*<<< orphan*/ ) ; 
 int cmsChannelsOf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsUInt32Number MakeFormatDescriptor(cmsColorSpaceSignature ColorSpace, int Bytes)
{
	int IsFloat = (Bytes == 0 || Bytes == 4) ? 1 : 0;
	int Channels = cmsChannelsOf(ColorSpace);
	return FLOAT_SH(IsFloat)|COLORSPACE_SH(_cmsLCMScolorSpace(ColorSpace))|BYTES_SH(Bytes)|CHANNELS_SH(Channels)|PLANAR_SH(1);
}