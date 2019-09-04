#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  outputThreadArg ;
typedef  int /*<<< orphan*/  fcr ;
struct TYPE_5__ {int /*<<< orphan*/ * srcFile; int /*<<< orphan*/  ctx; TYPE_3__* otArg; } ;
typedef  TYPE_1__ fcResources ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/ * dstFile; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 size_t MAX_NUM_JOBS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  createCCtx (size_t const) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,int,char*,char const* const) ; 
 int /*<<< orphan*/ * stdin ; 
 char const* const stdinmark ; 
 int /*<<< orphan*/ * stdout ; 
 char const* const stdoutmark ; 
 int /*<<< orphan*/  strcmp (char const*,char const* const) ; 

__attribute__((used)) static fcResources createFileCompressionResources(const char* const srcFilename, const char* const dstFilenameOrNull)
{
    fcResources fcr;
    unsigned const stdinUsed = !strcmp(srcFilename, stdinmark);
    FILE* const srcFile = stdinUsed ? stdin : fopen(srcFilename, "rb");
    const char* const outFilenameIntermediate = (stdinUsed && !dstFilenameOrNull) ? stdoutmark : dstFilenameOrNull;
    const char* outFilename = outFilenameIntermediate;
    char fileAndSuffix[MAX_PATH];
    size_t const numJobs = MAX_NUM_JOBS;

    memset(&fcr, 0, sizeof(fcr));

    if (!outFilenameIntermediate) {
        if (snprintf(fileAndSuffix, MAX_PATH, "%s.zst", srcFilename) + 1 > MAX_PATH) {
            DISPLAY("Error: output filename is too long\n");
            return fcr;
        }
        outFilename = fileAndSuffix;
    }

    {
        unsigned const stdoutUsed = !strcmp(outFilename, stdoutmark);
        FILE* const dstFile = stdoutUsed ? stdout : fopen(outFilename, "wb");
        fcr.otArg = malloc(sizeof(outputThreadArg));
        if (!fcr.otArg) {
            DISPLAY("Error: could not allocate space for output thread argument\n");
            return fcr;
        }
        fcr.otArg->dstFile = dstFile;
    }
    /* checking for errors */
    if (!fcr.otArg->dstFile || !srcFile) {
        DISPLAY("Error: some file(s) could not be opened\n");
        return fcr;
    }

    /* creating context */
    fcr.ctx = createCCtx(numJobs);
    fcr.otArg->ctx = fcr.ctx;
    fcr.srcFile = srcFile;
    return fcr;
}