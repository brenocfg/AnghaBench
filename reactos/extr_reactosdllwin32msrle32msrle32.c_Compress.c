#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ biSizeImage; int biBitCount; } ;
struct TYPE_15__ {scalar_t__ nPrevFrame; void* pCurFrame; void* pPrevFrame; int /*<<< orphan*/  bCompress; } ;
struct TYPE_14__ {int dwFlags; int* lpdwFlags; scalar_t__ lFrameNum; scalar_t__ dwFrameSize; int dwQuality; int /*<<< orphan*/ * lpckid; TYPE_5__* lpbiOutput; int /*<<< orphan*/  lpOutput; int /*<<< orphan*/ * lpInput; int /*<<< orphan*/ * lpbiInput; int /*<<< orphan*/ * lpPrev; int /*<<< orphan*/ * lpbiPrev; } ;
typedef  scalar_t__ LRESULT ;
typedef  void* LPWORD ;
typedef  TYPE_1__ ICCOMPRESS ;
typedef  int DWORD ;
typedef  TYPE_2__ CodecInfo ;
typedef  int BOOL ;

/* Variables and functions */
 int AVIIF_KEYFRAME ; 
 int AVIIF_TWOCC ; 
 scalar_t__ CompressBegin (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ CompressQuery (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int ICCOMPRESS_KEYFRAME ; 
 scalar_t__ ICERR_BADFORMAT ; 
 scalar_t__ ICERR_BADPARAM ; 
 scalar_t__ ICERR_GOTOKEYFRAME ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  MAKEAVICKID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSRLE32_CompressRLE4 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSRLE32_CompressRLE8 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StreamFromFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cktypeDIBbits ; 
 int /*<<< orphan*/  computeInternalFrame (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT Compress(CodecInfo *pi, ICCOMPRESS* lpic, DWORD dwSize)
{
  BOOL is_key;
  int i;

  TRACE("(%p,%p,%u)\n",pi,lpic,dwSize);

  /* pre-condition */
  assert(pi != NULL);

  /* check parameters */
  if (lpic == NULL || dwSize < sizeof(ICCOMPRESS))
    return ICERR_BADPARAM;
  if (!lpic->lpbiOutput || !lpic->lpOutput ||
      !lpic->lpbiInput  || !lpic->lpInput)
    return ICERR_BADPARAM;

  TRACE("lpic={0x%X,%p,%p,%p,%p,%p,%p,%d,%u,%u,%p,%p}\n",lpic->dwFlags,lpic->lpbiOutput,lpic->lpOutput,lpic->lpbiInput,lpic->lpInput,lpic->lpckid,lpic->lpdwFlags,lpic->lFrameNum,lpic->dwFrameSize,lpic->dwQuality,lpic->lpbiPrev,lpic->lpPrev);

  if (! pi->bCompress) {
    LRESULT hr = CompressBegin(pi, lpic->lpbiInput, lpic->lpbiOutput);
    if (hr != ICERR_OK)
      return hr;
  } else if (CompressQuery(pi, lpic->lpbiInput, lpic->lpbiOutput) != ICERR_OK)
    return ICERR_BADFORMAT;

  if (lpic->lFrameNum >= pi->nPrevFrame + 1) {
    /* we continue in the sequence so we need to initialize 
     * our internal framedata */

    computeInternalFrame(pi, lpic->lpbiInput, lpic->lpInput);
  } else if (lpic->lFrameNum == pi->nPrevFrame) {
    /* Oops, compress same frame again ? Okay, as you wish.
     * No need to recompute internal framedata, because we only swapped buffers */
    LPWORD pTmp = pi->pPrevFrame;

    pi->pPrevFrame = pi->pCurFrame;
    pi->pCurFrame  = pTmp;
  } else if ((lpic->dwFlags & ICCOMPRESS_KEYFRAME) == 0) {
    LPWORD pTmp;

    WARN(": prev=%d cur=%d gone back? -- untested\n",pi->nPrevFrame,lpic->lFrameNum);
    if (lpic->lpbiPrev == NULL || lpic->lpPrev == NULL)
      return ICERR_GOTOKEYFRAME; /* Need a keyframe if you go back */
    if (CompressQuery(pi, lpic->lpbiPrev, lpic->lpbiOutput) != ICERR_OK)
      return ICERR_BADFORMAT;

    WARN(": prev=%d cur=%d compute swapped -- untested\n",pi->nPrevFrame,lpic->lFrameNum);
    computeInternalFrame(pi, lpic->lpbiPrev, lpic->lpPrev);

    /* swap buffers for current and previous frame */
    /* Don't free and alloc new -- costs too much time and they are of equal size ! */
    pTmp = pi->pPrevFrame;
    pi->pPrevFrame = pi->pCurFrame;
    pi->pCurFrame  = pTmp;
    pi->nPrevFrame = lpic->lFrameNum;
  }

  is_key = (lpic->dwFlags & ICCOMPRESS_KEYFRAME) != 0;

  for (i = 0; i < 3; i++) {
    lpic->lpbiOutput->biSizeImage = 0;

    if (lpic->lpbiOutput->biBitCount == 4)
      MSRLE32_CompressRLE4(pi, lpic->lpbiInput, lpic->lpInput, lpic->lpbiOutput, lpic->lpOutput, is_key);
    else
      MSRLE32_CompressRLE8(pi, lpic->lpbiInput, lpic->lpInput, lpic->lpbiOutput, lpic->lpOutput, is_key);

    if (lpic->dwFrameSize == 0 ||
	lpic->lpbiOutput->biSizeImage < lpic->dwFrameSize)
      break;

    if ((*lpic->lpdwFlags & ICCOMPRESS_KEYFRAME) == 0) {
      if (lpic->lpbiOutput->biBitCount == 4)
        MSRLE32_CompressRLE4(pi, lpic->lpbiInput, lpic->lpInput,
                             lpic->lpbiOutput, lpic->lpOutput, TRUE);
      else
        MSRLE32_CompressRLE8(pi, lpic->lpbiInput, lpic->lpInput,
                             lpic->lpbiOutput, lpic->lpOutput, TRUE);

      if (lpic->dwFrameSize == 0 ||
	  lpic->lpbiOutput->biSizeImage < lpic->dwFrameSize) {
	WARN("switched to keyframe, was small enough!\n");
        is_key = TRUE;
	*lpic->lpckid    = MAKEAVICKID(cktypeDIBbits,
				       StreamFromFOURCC(*lpic->lpckid));
	break;
      }
    }

    if (lpic->dwQuality < 1000)
      break;

    lpic->dwQuality -= 1000; /* reduce quality by 10% */
  }

  { /* swap buffer for current and previous frame */
    /* Don't free and alloc new -- costs too much time and they are of equal size ! */
    LPWORD pTmp = pi->pPrevFrame;

    pi->pPrevFrame = pi->pCurFrame;
    pi->pCurFrame  = pTmp;
    pi->nPrevFrame = lpic->lFrameNum;
  }

  /* FIXME: What is AVIIF_TWOCC? */
  *lpic->lpdwFlags |= AVIIF_TWOCC | (is_key ? AVIIF_KEYFRAME : 0);
  return ICERR_OK;
}