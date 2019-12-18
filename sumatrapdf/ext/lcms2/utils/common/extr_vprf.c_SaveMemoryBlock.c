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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatalError (char*,char const*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

cmsBool SaveMemoryBlock(const cmsUInt8Number* Buffer, cmsUInt32Number dwLen, const char* Filename)
{
    FILE* out = fopen(Filename, "wb");
    if (out == NULL) {
        FatalError("Cannot create '%s'", Filename);
        return FALSE;
    }

    if (fwrite(Buffer, 1, dwLen, out) != dwLen) {
        FatalError("Cannot write %ld bytes to %s", dwLen, Filename);
        return FALSE;
    }

    if (fclose(out) != 0) {
        FatalError("Error flushing file '%s'", Filename);
        return FALSE;
    }

    return TRUE;
}