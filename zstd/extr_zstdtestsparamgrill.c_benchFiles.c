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
typedef  int /*<<< orphan*/  contexts_t ;
typedef  int /*<<< orphan*/  buffers_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_generate_cLevelTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int benchOnce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ createBuffers (int /*<<< orphan*/ *,char const**,int) ; 
 scalar_t__ createContexts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  freeBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeContexts (int /*<<< orphan*/ ) ; 
 scalar_t__ g_singleRun ; 

__attribute__((used)) static int benchFiles(const char** fileNamesTable, int nbFiles,
                      const char* dictFileName, int cLevel)
{
    buffers_t buf;
    contexts_t ctx;
    int ret = 0;

    if (createBuffers(&buf, fileNamesTable, nbFiles)) {
        DISPLAY("unable to load files\n");
        return 1;
    }

    if (createContexts(&ctx, dictFileName)) {
        DISPLAY("unable to load dictionary\n");
        freeBuffers(buf);
        return 2;
    }

    DISPLAY("\r%79s\r", "");
    if (nbFiles == 1) {
        DISPLAY("using %s : \n", fileNamesTable[0]);
    } else {
        DISPLAY("using %d Files : \n", nbFiles);
    }

    if (g_singleRun) {
        ret = benchOnce(buf, ctx, cLevel);
    } else {
        BMK_generate_cLevelTable(buf, ctx);
    }

    freeBuffers(buf);
    freeContexts(ctx);
    return ret;
}