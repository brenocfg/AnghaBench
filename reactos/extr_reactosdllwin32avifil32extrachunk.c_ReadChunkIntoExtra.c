#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cb; scalar_t__* lp; } ;
struct TYPE_5__ {scalar_t__ cksize; int /*<<< orphan*/  dwDataOffset; scalar_t__ ckid; } ;
typedef  TYPE_1__ MMCKINFO ;
typedef  TYPE_2__* LPEXTRACHUNKS ;
typedef  scalar_t__* LPDWORD ;
typedef  scalar_t__ LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HPSTR ;
typedef  int /*<<< orphan*/ * HMMIO ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_FILEREAD ; 
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ mmioRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int mmioSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT ReadChunkIntoExtra(LPEXTRACHUNKS extra,HMMIO hmmio,const MMCKINFO *lpck)
{
  LPDWORD lp;
  DWORD   cb;

  /* pre-conditions */
  assert(extra != NULL);
  assert(hmmio != NULL);
  assert(lpck  != NULL);

  cb  = lpck->cksize + 2 * sizeof(DWORD);
  cb += (cb & 1);

  if (extra->lp != NULL)
    lp = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, extra->lp, extra->cb + cb);
  else
    lp = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cb);

  if (lp == NULL)
    return AVIERR_MEMORY;

  extra->lp  = lp;
  lp = (LPDWORD) ((LPBYTE)lp + extra->cb);
  extra->cb += cb;

  /* insert chunk-header in block */
  lp[0] = lpck->ckid;
  lp[1] = lpck->cksize;

  if (lpck->cksize > 0) {
    if (mmioSeek(hmmio, lpck->dwDataOffset, SEEK_SET) == -1)
      return AVIERR_FILEREAD;
    if (mmioRead(hmmio, (HPSTR)&lp[2], lpck->cksize) != (LONG)lpck->cksize)
      return AVIERR_FILEREAD;
  }

  return AVIERR_OK;
}