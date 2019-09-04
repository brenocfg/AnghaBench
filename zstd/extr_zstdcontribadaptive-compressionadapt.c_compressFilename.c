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
struct TYPE_4__ {int /*<<< orphan*/  otArg; int /*<<< orphan*/  srcFile; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ fcResources ;

/* Variables and functions */
 TYPE_1__ createFileCompressionResources (char const* const,char const* const) ; 
 int freeFileCompressionResources (TYPE_1__*) ; 
 scalar_t__ g_streamedSize ; 
 int performCompression (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compressFilename(const char* const srcFilename, const char* const dstFilenameOrNull)
{
    int ret = 0;
    fcResources fcr = createFileCompressionResources(srcFilename, dstFilenameOrNull);
    g_streamedSize = 0;
    ret |= performCompression(fcr.ctx, fcr.srcFile, fcr.otArg);
    ret |= freeFileCompressionResources(&fcr);
    return ret;
}