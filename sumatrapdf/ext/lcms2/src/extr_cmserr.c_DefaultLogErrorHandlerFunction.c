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
typedef  char const* cmsUInt32Number ;
typedef  char const* cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (char const*) ; 

__attribute__((used)) static
void DefaultLogErrorHandlerFunction(cmsContext ContextID, cmsUInt32Number ErrorCode, const char *Text)
{
    // fprintf(stderr, "[lcms]: %s\n", Text);
    // fflush(stderr);

     cmsUNUSED_PARAMETER(ContextID);
     cmsUNUSED_PARAMETER(ErrorCode);
     cmsUNUSED_PARAMETER(Text);
}