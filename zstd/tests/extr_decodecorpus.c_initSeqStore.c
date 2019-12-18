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
struct TYPE_4__ {int /*<<< orphan*/  ofCode; int /*<<< orphan*/  mlCode; int /*<<< orphan*/  llCode; int /*<<< orphan*/  litStart; int /*<<< orphan*/  sequencesStart; int /*<<< orphan*/  maxNbLit; int /*<<< orphan*/  maxNbSeq; } ;
typedef  TYPE_1__ seqStore_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NB_SEQ ; 
 int /*<<< orphan*/  SEQUENCE_BUFFER ; 
 int /*<<< orphan*/  SEQUENCE_LITERAL_BUFFER ; 
 int /*<<< orphan*/  SEQUENCE_LLCODE ; 
 int /*<<< orphan*/  SEQUENCE_MLCODE ; 
 int /*<<< orphan*/  SEQUENCE_OFCODE ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_MAX ; 
 int /*<<< orphan*/  ZSTD_resetSeqStore (TYPE_1__*) ; 

__attribute__((used)) static inline void initSeqStore(seqStore_t *seqStore) {
    seqStore->maxNbSeq = MAX_NB_SEQ;
    seqStore->maxNbLit = ZSTD_BLOCKSIZE_MAX;
    seqStore->sequencesStart = SEQUENCE_BUFFER;
    seqStore->litStart = SEQUENCE_LITERAL_BUFFER;
    seqStore->llCode = SEQUENCE_LLCODE;
    seqStore->mlCode = SEQUENCE_MLCODE;
    seqStore->ofCode = SEQUENCE_OFCODE;

    ZSTD_resetSeqStore(seqStore);
}