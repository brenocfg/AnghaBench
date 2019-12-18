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
typedef  scalar_t__ genType_e ;
struct TYPE_4__ {scalar_t__ srcStart; scalar_t__ src; scalar_t__ dataStart; scalar_t__ data; } ;
typedef  TYPE_1__ frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  DISPLAYUPDATE (char*,unsigned int,unsigned int) ; 
 int MAX_PATH ; 
 scalar_t__ generateCompressedBlock (scalar_t__,TYPE_1__*,int /*<<< orphan*/  const) ; 
 scalar_t__ generateFrame (scalar_t__,TYPE_1__*,int /*<<< orphan*/  const) ; 
 scalar_t__ gt_frame ; 
 int /*<<< orphan*/  initDictInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outputBuffer (scalar_t__,int,char*) ; 
 int snprintf (char*,int,char*,char const* const,unsigned int) ; 

__attribute__((used)) static int generateCorpus(U32 seed, unsigned numFiles, const char* const path,
                          const char* const origPath, genType_e genType)
{
    char outPath[MAX_PATH];
    unsigned fnum;

    DISPLAY("seed: %u\n", (unsigned)seed);

    for (fnum = 0; fnum < numFiles; fnum++) {
        frame_t fr;

        DISPLAYUPDATE("\r%u/%u        ", fnum, numFiles);

        {   dictInfo const info = initDictInfo(0, 0, NULL, 0);
            if (genType == gt_frame) {
                seed = generateFrame(seed, &fr, info);
            } else {
                seed = generateCompressedBlock(seed, &fr, info);
            }
        }

        if (snprintf(outPath, MAX_PATH, "%s/z%06u.zst", path, fnum) + 1 > MAX_PATH) {
            DISPLAY("Error: path too long\n");
            return 1;
        }
        outputBuffer(fr.dataStart, (BYTE*)fr.data - (BYTE*)fr.dataStart, outPath);

        if (origPath) {
            if (snprintf(outPath, MAX_PATH, "%s/z%06u", origPath, fnum) + 1 > MAX_PATH) {
                DISPLAY("Error: path too long\n");
                return 1;
            }
            outputBuffer(fr.srcStart, (BYTE*)fr.src - (BYTE*)fr.srcStart, outPath);
        }
    }

    DISPLAY("\r%u/%u      \n", fnum, numFiles);

    return 0;
}