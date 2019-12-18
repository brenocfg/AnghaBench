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
struct TYPE_4__ {int member_0; int member_1; } ;
typedef  TYPE_1__ tjscalingfactor ;
typedef  int /*<<< orphan*/  tjhandle ;

/* Variables and functions */
 int TJSAMP_444 ; 
 int TJSAMP_GRAY ; 
 int /*<<< orphan*/  _decompTest (int /*<<< orphan*/ ,unsigned char*,unsigned long,int,int,int,char*,int,int,TYPE_1__) ; 
 int /*<<< orphan*/  _throwtj () ; 
 TYPE_1__* tjGetScalingFactors (int*) ; 
 int /*<<< orphan*/  yuv ; 

void decompTest(tjhandle handle, unsigned char *jpegBuf,
	unsigned long jpegSize, int w, int h, int pf, char *basename, int subsamp,
	int flags)
{
	int i, n=0;
	tjscalingfactor *sf=tjGetScalingFactors(&n), sf1={1, 1};
	if(!sf || !n) _throwtj();

	if((subsamp==TJSAMP_444 || subsamp==TJSAMP_GRAY) && !yuv)
	{
		for(i=0; i<n; i++)
			_decompTest(handle, jpegBuf, jpegSize, w, h, pf, basename, subsamp,
				flags, sf[i]);
	}
	else
		_decompTest(handle, jpegBuf, jpegSize, w, h, pf, basename, subsamp, flags,
			sf1);

	bailout:
	return;
}