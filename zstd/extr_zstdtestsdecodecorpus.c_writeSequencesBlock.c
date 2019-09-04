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
typedef  int /*<<< orphan*/  seqStore_t ;
typedef  int /*<<< orphan*/  frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKERR (int /*<<< orphan*/ ) ; 
 size_t generateSequences (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initSeqStore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeSequences (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t writeSequencesBlock(U32* seed, frame_t* frame, size_t contentSize,
                                  size_t literalsSize, dictInfo info)
{
    seqStore_t seqStore;
    size_t numSequences;


    initSeqStore(&seqStore);

    /* randomly generate sequences */
    numSequences = generateSequences(seed, frame, &seqStore, contentSize, literalsSize, info);
    /* write them out to the frame data */
    CHECKERR(writeSequences(seed, frame, &seqStore, numSequences));

    return numSequences;
}