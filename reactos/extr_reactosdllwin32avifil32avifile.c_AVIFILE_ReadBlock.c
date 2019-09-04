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
struct TYPE_6__ {scalar_t__ dwStart; scalar_t__ dwLength; int /*<<< orphan*/  dwSuggestedBufferSize; } ;
struct TYPE_9__ {scalar_t__ lLastFrame; scalar_t__* lpBuffer; scalar_t__ cbBuffer; TYPE_3__* paf; TYPE_2__* idxFrames; TYPE_1__ sInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hmmio; } ;
struct TYPE_7__ {scalar_t__ dwChunkLength; scalar_t__ ckid; scalar_t__ dwChunkOffset; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  TYPE_4__ IAVIStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HPSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_FILEREAD ; 
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  ERR (char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 void* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int mmioSeek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT AVIFILE_ReadBlock(IAVIStreamImpl *This, DWORD pos,
				 LPVOID buffer, DWORD size)
{
  /* pre-conditions */
  assert(This != NULL);
  assert(This->paf != NULL);
  assert(This->paf->hmmio != NULL);
  assert(This->sInfo.dwStart <= pos && pos < This->sInfo.dwLength);
  assert(pos <= This->lLastFrame);

  /* should we read as much as block gives us? */
  if (size == 0 || size > This->idxFrames[pos].dwChunkLength)
    size = This->idxFrames[pos].dwChunkLength;

  /* read into out own buffer or given one? */
  if (buffer == NULL) {
    /* we also read the chunk */
    size += 2 * sizeof(DWORD);

    /* check that buffer is big enough -- don't trust dwSuggestedBufferSize */
    if (This->lpBuffer == NULL || This->cbBuffer < size) {
      DWORD maxSize = max(size, This->sInfo.dwSuggestedBufferSize);

      if (This->lpBuffer == NULL) {
	This->lpBuffer = HeapAlloc(GetProcessHeap(), 0, maxSize);
        if (!This->lpBuffer) return AVIERR_MEMORY;
      } else {
        void *new_buffer = HeapReAlloc(GetProcessHeap(), 0, This->lpBuffer, maxSize);
        if (!new_buffer) return AVIERR_MEMORY;
        This->lpBuffer = new_buffer;
      }
      This->cbBuffer = maxSize;
    }

    /* now read the complete chunk into our buffer */
    if (mmioSeek(This->paf->hmmio, This->idxFrames[pos].dwChunkOffset, SEEK_SET) == -1)
      return AVIERR_FILEREAD;
    if (mmioRead(This->paf->hmmio, (HPSTR)This->lpBuffer, size) != size)
      return AVIERR_FILEREAD;

    /* check if it was the correct block which we have read */
    if (This->lpBuffer[0] != This->idxFrames[pos].ckid ||
	This->lpBuffer[1] != This->idxFrames[pos].dwChunkLength) {
      ERR(": block %d not found at 0x%08X\n", pos, This->idxFrames[pos].dwChunkOffset);
      ERR(": Index says: '%4.4s'(0x%08X) size 0x%08X\n",
	  (char*)&This->idxFrames[pos].ckid, This->idxFrames[pos].ckid,
	  This->idxFrames[pos].dwChunkLength);
      ERR(": Data  says: '%4.4s'(0x%08X) size 0x%08X\n",
	  (char*)&This->lpBuffer[0], This->lpBuffer[0], This->lpBuffer[1]);
      return AVIERR_FILEREAD;
    }
  } else {
    if (mmioSeek(This->paf->hmmio, This->idxFrames[pos].dwChunkOffset + 2 * sizeof(DWORD), SEEK_SET) == -1)
      return AVIERR_FILEREAD;
    if (mmioRead(This->paf->hmmio, buffer, size) != size)
      return AVIERR_FILEREAD;
  }

  return AVIERR_OK;
}