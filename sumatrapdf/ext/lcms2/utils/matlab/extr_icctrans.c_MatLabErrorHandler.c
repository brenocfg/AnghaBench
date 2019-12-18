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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  mexErrMsgTxt (char const*) ; 

__attribute__((used)) static
void MatLabErrorHandler(cmsContext ContextID, cmsUInt32Number ErrorCode, 
						const char *Text)
{      
	mexErrMsgTxt(Text);    
}