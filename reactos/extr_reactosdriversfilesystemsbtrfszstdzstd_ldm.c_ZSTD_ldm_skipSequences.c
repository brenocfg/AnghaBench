#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pos; scalar_t__ size; TYPE_2__* seq; } ;
typedef  TYPE_1__ rawSeqStore_t ;
struct TYPE_5__ {size_t litLength; size_t matchLength; } ;
typedef  TYPE_2__ rawSeq ;
typedef  size_t U32 ;

/* Variables and functions */

void ZSTD_ldm_skipSequences(rawSeqStore_t* rawSeqStore, size_t srcSize, U32 const minMatch) {
    while (srcSize > 0 && rawSeqStore->pos < rawSeqStore->size) {
        rawSeq* seq = rawSeqStore->seq + rawSeqStore->pos;
        if (srcSize <= seq->litLength) {
            /* Skip past srcSize literals */
            seq->litLength -= (U32)srcSize;
            return;
        }
        srcSize -= seq->litLength;
        seq->litLength = 0;
        if (srcSize < seq->matchLength) {
            /* Skip past the first srcSize of the match */
            seq->matchLength -= (U32)srcSize;
            if (seq->matchLength < minMatch) {
                /* The match is too short, omit it */
                if (rawSeqStore->pos + 1 < rawSeqStore->size) {
                    seq[1].litLength += seq[0].matchLength;
                }
                rawSeqStore->pos++;
            }
            return;
        }
        srcSize -= seq->matchLength;
        seq->matchLength = 0;
        rawSeqStore->pos++;
    }
}