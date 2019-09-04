#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sInfo ;
struct TYPE_13__ {int dwStreams; int dwScale; int dwRate; scalar_t__ dwSuggestedBufferSize; scalar_t__ dwLength; scalar_t__ dwWidth; scalar_t__ dwHeight; } ;
struct TYPE_9__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_12__ {int dwScale; int dwRate; scalar_t__ dwSuggestedBufferSize; TYPE_1__ rcFrame; int /*<<< orphan*/  dwLength; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_2__ IAVIFile_iface; TYPE_5__ fInfo; int /*<<< orphan*/ * ppStreams; } ;
typedef  int /*<<< orphan*/  PAVISTREAM ;
typedef  TYPE_2__* PAVIFILE ;
typedef  TYPE_3__ ITmpFileImpl ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ AVISTREAMINFOW ;

/* Variables and functions */
 int /*<<< orphan*/  AVIStreamAddRef (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  AVIStreamInfoW (int /*<<< orphan*/  const,TYPE_4__*,int) ; 
 int /*<<< orphan*/  AVIStreamSampleToTime (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ MulDiv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  itmpft ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

PAVIFILE AVIFILE_CreateAVITempFile(int nStreams, const PAVISTREAM *ppStreams)
{
  ITmpFileImpl *tmpFile;
  int           i;

  tmpFile = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ITmpFileImpl));
  if (tmpFile == NULL)
    return NULL;

  tmpFile->IAVIFile_iface.lpVtbl = &itmpft;
  tmpFile->ref    = 1;
  memset(&tmpFile->fInfo, 0, sizeof(tmpFile->fInfo));

  tmpFile->fInfo.dwStreams = nStreams;
  tmpFile->ppStreams = HeapAlloc(GetProcessHeap(), 0, nStreams * sizeof(PAVISTREAM));
  if (tmpFile->ppStreams == NULL) {
    HeapFree(GetProcessHeap(), 0, tmpFile);
    return NULL;
  }

  for (i = 0; i < nStreams; i++) {
    AVISTREAMINFOW sInfo;

    tmpFile->ppStreams[i] = ppStreams[i];

    AVIStreamAddRef(ppStreams[i]);
    AVIStreamInfoW(ppStreams[i], &sInfo, sizeof(sInfo));
    if (i == 0) {
      tmpFile->fInfo.dwScale = sInfo.dwScale;
      tmpFile->fInfo.dwRate  = sInfo.dwRate;
      if (!sInfo.dwScale || !sInfo.dwRate) {
        tmpFile->fInfo.dwScale = 1;
        tmpFile->fInfo.dwRate  = 100;
      }
    }

    if (tmpFile->fInfo.dwSuggestedBufferSize < sInfo.dwSuggestedBufferSize)
      tmpFile->fInfo.dwSuggestedBufferSize = sInfo.dwSuggestedBufferSize;

    {
      DWORD tmp;

      tmp = MulDiv(AVIStreamSampleToTime(ppStreams[i], sInfo.dwLength),
                   tmpFile->fInfo.dwScale, tmpFile->fInfo.dwRate * 1000);
      if (tmpFile->fInfo.dwLength < tmp)
        tmpFile->fInfo.dwLength = tmp;

      tmp = sInfo.rcFrame.right - sInfo.rcFrame.left;
      if (tmpFile->fInfo.dwWidth < tmp)
        tmpFile->fInfo.dwWidth = tmp;
      tmp = sInfo.rcFrame.bottom - sInfo.rcFrame.top;
      if (tmpFile->fInfo.dwHeight < tmp)
        tmpFile->fInfo.dwHeight = tmp;
    }
  }

  return &tmpFile->IAVIFile_iface;
}