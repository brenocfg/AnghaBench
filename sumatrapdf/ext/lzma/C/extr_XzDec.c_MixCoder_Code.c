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
struct TYPE_7__ {scalar_t__ (* Alloc ) (TYPE_3__*,int) ;} ;
struct TYPE_6__ {scalar_t__ buf; int numCoders; int* pos; scalar_t__* size; int* finished; TYPE_1__* coders; TYPE_3__* alloc; } ;
struct TYPE_5__ {scalar_t__ (* Code ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__*,int,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  p; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ IStateCoder ;
typedef  int /*<<< orphan*/  ECoderStatus ;
typedef  int /*<<< orphan*/  ECoderFinishMode ;
typedef  TYPE_2__ CMixCoder ;
typedef  int /*<<< orphan*/  Byte ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int CODER_BUF_SIZE ; 
 int /*<<< orphan*/  CODER_FINISH_ANY ; 
 int /*<<< orphan*/  CODER_STATUS_FINISHED_WITH_MARK ; 
 int /*<<< orphan*/  CODER_STATUS_NOT_FINISHED ; 
 scalar_t__ False ; 
 int MIXCODER_NUM_FILTERS_MAX ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ True ; 
 scalar_t__ stub1 (TYPE_3__*,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__*,int,int /*<<< orphan*/ ,int*) ; 

SRes MixCoder_Code(CMixCoder *p, Byte *dest, SizeT *destLen,
    const Byte *src, SizeT *srcLen, int srcWasFinished,
    ECoderFinishMode finishMode, ECoderStatus *status)
{
  SizeT destLenOrig = *destLen;
  SizeT srcLenOrig = *srcLen;
  Bool allFinished = True;
  *destLen = 0;
  *srcLen = 0;
  *status = CODER_STATUS_NOT_FINISHED;

  if (p->buf == 0)
  {
    p->buf = p->alloc->Alloc(p->alloc, CODER_BUF_SIZE * (MIXCODER_NUM_FILTERS_MAX - 1));
    if (p->buf == 0)
      return SZ_ERROR_MEM;
  }

  if (p->numCoders != 1)
    finishMode = CODER_FINISH_ANY;

  for (;;)
  {
    Bool processed = False;
    int i;
    /*
    if (p->numCoders == 1 && *destLen == destLenOrig && finishMode == LZMA_FINISH_ANY)
      break;
    */

    for (i = 0; i < p->numCoders; i++)
    {
      SRes res;
      IStateCoder *coder = &p->coders[i];
      Byte *destCur;
      SizeT destLenCur, srcLenCur;
      const Byte *srcCur;
      int srcFinishedCur;
      int encodingWasFinished;
      
      if (i == 0)
      {
        srcCur = src;
        srcLenCur = srcLenOrig - *srcLen;
        srcFinishedCur = srcWasFinished;
      }
      else
      {
        srcCur = p->buf + (CODER_BUF_SIZE * (i - 1)) + p->pos[i - 1];
        srcLenCur = p->size[i - 1] - p->pos[i - 1];
        srcFinishedCur = p->finished[i - 1];
      }
      
      if (i == p->numCoders - 1)
      {
        destCur = dest;
        destLenCur = destLenOrig - *destLen;
      }
      else
      {
        if (p->pos[i] != p->size[i])
          continue;
        destCur = p->buf + (CODER_BUF_SIZE * i);
        destLenCur = CODER_BUF_SIZE;
      }
      
      res = coder->Code(coder->p, destCur, &destLenCur, srcCur, &srcLenCur, srcFinishedCur, finishMode, &encodingWasFinished);

      if (!encodingWasFinished)
        allFinished = False;

      if (i == 0)
      {
        *srcLen += srcLenCur;
        src += srcLenCur;
      }
      else
      {
        p->pos[i - 1] += srcLenCur;
      }

      if (i == p->numCoders - 1)
      {
        *destLen += destLenCur;
        dest += destLenCur;
      }
      else
      {
        p->size[i] = destLenCur;
        p->pos[i] = 0;
        p->finished[i] = encodingWasFinished;
      }
      
      if (res != SZ_OK)
        return res;

      if (destLenCur != 0 || srcLenCur != 0)
        processed = True;
    }
    if (!processed)
      break;
  }
  if (allFinished)
    *status = CODER_STATUS_FINISHED_WITH_MARK;
  return SZ_OK;
}