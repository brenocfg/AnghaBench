#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t dwSampleSize; size_t dwStart; } ;
struct TYPE_7__ {size_t lLastFrame; TYPE_2__* idxFrames; TYPE_1__ sInfo; } ;
struct TYPE_6__ {size_t dwChunkLength; } ;
typedef  size_t* LPLONG ;
typedef  size_t LONG ;
typedef  TYPE_3__ IAVIStreamImpl ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void AVIFILE_SamplesToBlock(const IAVIStreamImpl *This, LPLONG pos, LPLONG offset)
{
  LONG block;

  /* pre-conditions */
  assert(This != NULL);
  assert(pos != NULL);
  assert(offset != NULL);
  assert(This->sInfo.dwSampleSize != 0);
  assert(*pos >= This->sInfo.dwStart);

  /* convert start sample to start bytes */
  (*offset)  = (*pos) - This->sInfo.dwStart;
  (*offset) *= This->sInfo.dwSampleSize;

  /* convert bytes to block number */
  for (block = 0; block <= This->lLastFrame; block++) {
    if (This->idxFrames[block].dwChunkLength <= *offset)
      (*offset) -= This->idxFrames[block].dwChunkLength;
    else
      break;
  }

  *pos = block;
}