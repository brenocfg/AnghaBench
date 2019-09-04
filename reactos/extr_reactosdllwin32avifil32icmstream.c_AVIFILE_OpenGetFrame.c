#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ biHeight; scalar_t__ biWidth; } ;
struct TYPE_22__ {int biSizeImage; int biHeight; } ;
struct TYPE_19__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_20__ {scalar_t__ fccHandler; int /*<<< orphan*/  dwSuggestedBufferSize; TYPE_1__ rcFrame; int /*<<< orphan*/  dwStart; } ;
struct TYPE_21__ {int lKeyFrameEvery; int dwICMFlags; TYPE_4__* lpbiPrev; TYPE_5__* lpbiOutput; int /*<<< orphan*/ * hic; void* lpPrev; TYPE_4__* lpbiCur; void* lpCur; scalar_t__ cbOutput; TYPE_2__ sInfo; int /*<<< orphan*/ * pg; int /*<<< orphan*/ * pStream; } ;
typedef  int /*<<< orphan*/ * LPBITMAPINFOHEADER ;
typedef  scalar_t__ LONG ;
typedef  TYPE_3__ IAVIStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_BADFORMAT ; 
 int /*<<< orphan*/  AVIERR_COMPRESSOR ; 
 int /*<<< orphan*/  AVIERR_ERROR ; 
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/ * AVIStreamGetFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AVIStreamGetFrameOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* DIBPTR (TYPE_4__*) ; 
 int DIBWIDTHBYTES (TYPE_4__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 scalar_t__ ICCompressBegin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ICCompressGetFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ICCompressGetFormatSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICCompressGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ICDecompressBegin (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ ICDecompressGetFormat (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ ICDecompressGetFormatSize (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ S_OK ; 
 int VIDCF_FASTTEMPORALC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ comptypeDIB ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static HRESULT AVIFILE_OpenGetFrame(IAVIStreamImpl *This)
{
  LPBITMAPINFOHEADER lpbi;
  DWORD              size;

  /* pre-conditions */
  assert(This != NULL);
  assert(This->pStream != NULL);
  assert(This->pg == NULL);

  This->pg = AVIStreamGetFrameOpen(This->pStream, NULL);
  if (This->pg == NULL)
    return AVIERR_ERROR;

  /* When we only decompress this is enough */
  if (This->sInfo.fccHandler == comptypeDIB)
    return AVIERR_OK;

  assert(This->hic != NULL);
  assert(This->lpbiOutput == NULL);

  /* get input format */
  lpbi = AVIStreamGetFrame(This->pg, This->sInfo.dwStart);
  if (lpbi == NULL)
    return AVIERR_MEMORY;

  /* get memory for output format */
  size = ICCompressGetFormatSize(This->hic, lpbi);
  if ((LONG)size < (LONG)sizeof(BITMAPINFOHEADER))
    return AVIERR_COMPRESSOR;
  This->lpbiOutput = HeapAlloc(GetProcessHeap(), 0, size);
  if (This->lpbiOutput == NULL)
    return AVIERR_MEMORY;
  This->cbOutput = size;

  if (ICCompressGetFormat(This->hic, lpbi, This->lpbiOutput) < S_OK)
    return AVIERR_BADFORMAT;

  /* update AVISTREAMINFO structure */
  This->sInfo.rcFrame.right  =
    This->sInfo.rcFrame.left + This->lpbiOutput->biWidth;
  This->sInfo.rcFrame.bottom =
    This->sInfo.rcFrame.top  + This->lpbiOutput->biHeight;
  This->sInfo.dwSuggestedBufferSize =
    ICCompressGetSize(This->hic, lpbi, This->lpbiOutput);

  /* prepare codec for compression */
  if (ICCompressBegin(This->hic, lpbi, This->lpbiOutput) != S_OK)
    return AVIERR_COMPRESSOR;

  /* allocate memory for current frame */
  size += This->sInfo.dwSuggestedBufferSize;
  This->lpbiCur = HeapAlloc(GetProcessHeap(), 0, size);
  if (This->lpbiCur == NULL)
    return AVIERR_MEMORY;
  memcpy(This->lpbiCur, This->lpbiOutput, This->cbOutput);
  This->lpCur = DIBPTR(This->lpbiCur);

  /* allocate memory for last frame if needed */
  if (This->lKeyFrameEvery != 1 &&
      (This->dwICMFlags & VIDCF_FASTTEMPORALC) == 0) {
    size = ICDecompressGetFormatSize(This->hic, This->lpbiOutput);
    This->lpbiPrev = HeapAlloc(GetProcessHeap(), 0, size);
    if (This->lpbiPrev == NULL)
      return AVIERR_MEMORY;
    if (ICDecompressGetFormat(This->hic, This->lpbiOutput, This->lpbiPrev) < S_OK)
      return AVIERR_COMPRESSOR;

    if (This->lpbiPrev->biSizeImage == 0) {
      This->lpbiPrev->biSizeImage =
	DIBWIDTHBYTES(*This->lpbiPrev) * This->lpbiPrev->biHeight;
    }

    /* get memory for format and picture */
    size += This->lpbiPrev->biSizeImage;
    This->lpbiPrev = HeapReAlloc(GetProcessHeap(), 0, This->lpbiPrev, size );
    if (This->lpbiPrev == NULL)
      return AVIERR_MEMORY;
    This->lpPrev = DIBPTR(This->lpbiPrev);

    /* prepare codec also for decompression */
    if (ICDecompressBegin(This->hic,This->lpbiOutput,This->lpbiPrev) != S_OK)
      return AVIERR_COMPRESSOR;
  }

  return AVIERR_OK;
}