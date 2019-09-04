#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* DebugInfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* lpVtbl; } ;
struct TYPE_8__ {int refCount; int /*<<< orphan*/  mtCurrent; int /*<<< orphan*/  pinInfo; int /*<<< orphan*/  pCritSec; int /*<<< orphan*/ * pConnectedTo; TYPE_1__ IPin_iface; } ;
struct TYPE_10__ {int rtStop; double dRate; TYPE_6__ thread_lock; int /*<<< orphan*/  stop_playback; int /*<<< orphan*/  fnCustomRequest; int /*<<< orphan*/  state; scalar_t__ rtCurrent; scalar_t__ rtStart; void* thread_sleepy; void* hEventStateChanged; int /*<<< orphan*/ * hThread; int /*<<< orphan*/ * pReader; int /*<<< orphan*/ * prefAlloc; int /*<<< orphan*/ * pAlloc; int /*<<< orphan*/ * fnPreConnect; int /*<<< orphan*/  fnDone; int /*<<< orphan*/  fnCleanProc; int /*<<< orphan*/  fnSampleProc; int /*<<< orphan*/  fnQueryAccept; int /*<<< orphan*/  pUserData; TYPE_2__ pin; } ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  STOPPROCESSPROC ;
typedef  int /*<<< orphan*/  SAMPLEPROC_PULL ;
typedef  int /*<<< orphan*/  REQUESTPROC ;
typedef  int /*<<< orphan*/  QUERYACCEPTPROC ;
typedef  TYPE_4__ PullPin ;
typedef  int /*<<< orphan*/  PIN_INFO ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCRITICAL_SECTION ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  IPinVtbl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  CLEANUPPROC ;
typedef  int /*<<< orphan*/  AM_MEDIA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy_PinInfo (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_6__*) ; 
 int /*<<< orphan*/  Req_Die ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT PullPin_Init(const IPinVtbl *PullPin_Vtbl, const PIN_INFO * pPinInfo, SAMPLEPROC_PULL pSampleProc, LPVOID pUserData,
                            QUERYACCEPTPROC pQueryAccept, CLEANUPPROC pCleanUp, REQUESTPROC pCustomRequest, STOPPROCESSPROC pDone, LPCRITICAL_SECTION pCritSec, PullPin * pPinImpl)
{
    /* Common attributes */
    pPinImpl->pin.IPin_iface.lpVtbl = PullPin_Vtbl;
    pPinImpl->pin.refCount = 1;
    pPinImpl->pin.pConnectedTo = NULL;
    pPinImpl->pin.pCritSec = pCritSec;
    Copy_PinInfo(&pPinImpl->pin.pinInfo, pPinInfo);
    ZeroMemory(&pPinImpl->pin.mtCurrent, sizeof(AM_MEDIA_TYPE));

    /* Input pin attributes */
    pPinImpl->pUserData = pUserData;
    pPinImpl->fnQueryAccept = pQueryAccept;
    pPinImpl->fnSampleProc = pSampleProc;
    pPinImpl->fnCleanProc = pCleanUp;
    pPinImpl->fnDone = pDone;
    pPinImpl->fnPreConnect = NULL;
    pPinImpl->pAlloc = NULL;
    pPinImpl->prefAlloc = NULL;
    pPinImpl->pReader = NULL;
    pPinImpl->hThread = NULL;
    pPinImpl->hEventStateChanged = CreateEventW(NULL, TRUE, TRUE, NULL);
    pPinImpl->thread_sleepy = CreateEventW(NULL, FALSE, FALSE, NULL);

    pPinImpl->rtStart = 0;
    pPinImpl->rtCurrent = 0;
    pPinImpl->rtStop = ((LONGLONG)0x7fffffff << 32) | 0xffffffff;
    pPinImpl->dRate = 1.0;
    pPinImpl->state = Req_Die;
    pPinImpl->fnCustomRequest = pCustomRequest;
    pPinImpl->stop_playback = TRUE;

    InitializeCriticalSection(&pPinImpl->thread_lock);
    pPinImpl->thread_lock.DebugInfo->Spare[0] = (DWORD_PTR)( __FILE__ ": PullPin.thread_lock");

    return S_OK;
}