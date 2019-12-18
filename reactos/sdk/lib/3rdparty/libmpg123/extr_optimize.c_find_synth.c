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
typedef  scalar_t__ const func_synth ;
typedef  enum synth_resample { ____Placeholder_synth_resample } synth_resample ;
typedef  enum synth_format { ____Placeholder_synth_format } synth_format ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int f_limit ; 
 int r_limit ; 

__attribute__((used)) static int find_synth(func_synth synth,  const func_synth synths[r_limit][f_limit])
{
	enum synth_resample ri;
	enum synth_format   fi;
	for(ri=0; ri<r_limit; ++ri)
	for(fi=0; fi<f_limit; ++fi)
	if(synth == synths[ri][fi])
	return TRUE;

	return FALSE;
}