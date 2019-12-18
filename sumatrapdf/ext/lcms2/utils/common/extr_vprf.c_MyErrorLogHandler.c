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
 char* ProgramName ; 
 int /*<<< orphan*/  UTILS_UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void MyErrorLogHandler(cmsContext ContextID, cmsUInt32Number ErrorCode, const char *Text)
{
    if (Verbose >= 0)
        fprintf(stderr, "[%s]: %s\n", ProgramName, Text);

    UTILS_UNUSED_PARAMETER(ErrorCode);
    UTILS_UNUSED_PARAMETER(ContextID);
}