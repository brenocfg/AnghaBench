#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t dwStreams; } ;
struct TYPE_9__ {int dwMoviChunkPos; size_t dwNextFramePos; TYPE_3__** ppStreams; TYPE_1__ fInfo; } ;
struct TYPE_7__ {scalar_t__* szName; } ;
struct TYPE_8__ {int cbFormat; int cbHandlerData; TYPE_2__ sInfo; int /*<<< orphan*/ * lpHandlerData; } ;
typedef  int /*<<< orphan*/  MainAVIHeader ;
typedef  TYPE_3__ IAVIStreamImpl ;
typedef  TYPE_4__ IAVIFileImpl ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  AVIStreamHeader ;

/* Variables and functions */
 size_t AVI_HEADERSIZE ; 
 int lstrlenW (scalar_t__*) ; 

__attribute__((used)) static DWORD   AVIFILE_ComputeMoviStart(IAVIFileImpl *This)
{
  DWORD dwPos;
  DWORD nStream;

  /* RIFF,hdrl,movi,avih => (3 * 3 + 2) * sizeof(DWORD) = 11 * sizeof(DWORD) */
  dwPos = 11 * sizeof(DWORD) + sizeof(MainAVIHeader);

  for (nStream = 0; nStream < This->fInfo.dwStreams; nStream++) {
    IAVIStreamImpl *pStream = This->ppStreams[nStream];

    /* strl,strh,strf => (3 + 2 * 2) * sizeof(DWORD) = 7 * sizeof(DWORD) */
    dwPos += 7 * sizeof(DWORD) + sizeof(AVIStreamHeader);
    dwPos += ((pStream->cbFormat + 1) & ~1U);
    if (pStream->lpHandlerData != NULL && pStream->cbHandlerData > 0)
      dwPos += 2 * sizeof(DWORD) + ((pStream->cbHandlerData + 1) & ~1U);
    if (pStream->sInfo.szName[0])
      dwPos += 2 * sizeof(DWORD) + ((lstrlenW(pStream->sInfo.szName) + 1) & ~1U);
  }

  if (This->dwMoviChunkPos == 0) {
    This->dwNextFramePos = dwPos;

    /* pad to multiple of AVI_HEADERSIZE only if we are more than 8 bytes away from it */
    if (((dwPos + AVI_HEADERSIZE) & ~(AVI_HEADERSIZE - 1)) - dwPos > 2 * sizeof(DWORD))
      This->dwNextFramePos = (dwPos + AVI_HEADERSIZE) & ~(AVI_HEADERSIZE - 1);

    This->dwMoviChunkPos = This->dwNextFramePos - sizeof(DWORD);
  }

  return dwPos;
}