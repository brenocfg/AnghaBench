#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_9__ {TYPE_2__ filter; TYPE_1__* pInputPin; int /*<<< orphan*/  csRenderLock; } ;
struct TYPE_10__ {int in_loop; scalar_t__ buf_size; scalar_t__ writepos; int /*<<< orphan*/  dsbuffer; TYPE_3__ renderer; int /*<<< orphan*/  blocked; } ;
struct TYPE_7__ {scalar_t__ flushing; } ;
typedef  int REFERENCE_TIME ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ DSoundRenderImpl ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ DSoundRender_GetWritePos (TYPE_4__*,scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ IDirectSoundBuffer_Lock (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void**,scalar_t__*,void**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ State_Paused ; 
 scalar_t__ State_Running ; 
 scalar_t__ State_Stopped ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ VFW_E_WRONG_STATE ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT DSoundRender_SendSampleData(DSoundRenderImpl* This, REFERENCE_TIME tStart, REFERENCE_TIME tStop, const BYTE *data, DWORD size)
{
    HRESULT hr;

    while (size && This->renderer.filter.state != State_Stopped) {
        DWORD writepos, skip = 0, free, size1, size2, ret;
        BYTE *buf1, *buf2;

        if (This->renderer.filter.state == State_Running)
            hr = DSoundRender_GetWritePos(This, &writepos, tStart, &free, &skip);
        else
            hr = S_FALSE;

        if (hr != S_OK) {
            This->in_loop = 1;
            LeaveCriticalSection(&This->renderer.csRenderLock);
            ret = WaitForSingleObject(This->blocked, 10);
            EnterCriticalSection(&This->renderer.csRenderLock);
            This->in_loop = 0;
            if (This->renderer.pInputPin->flushing ||
                This->renderer.filter.state == State_Stopped) {
                return This->renderer.filter.state == State_Paused ? S_OK : VFW_E_WRONG_STATE;
            }
            if (ret != WAIT_TIMEOUT)
                ERR("%x\n", ret);
            continue;
        }
        tStart = -1;

        if (skip)
            FIXME("Sample dropped %u of %u bytes\n", skip, size);
        if (skip >= size)
            return S_OK;
        data += skip;
        size -= skip;

        hr = IDirectSoundBuffer_Lock(This->dsbuffer, writepos, min(free, size), (void**)&buf1, &size1, (void**)&buf2, &size2, 0);
        if (hr != DS_OK) {
            ERR("Unable to lock sound buffer! (%x)\n", hr);
            break;
        }
        memcpy(buf1, data, size1);
        if (size2)
            memcpy(buf2, data+size1, size2);
        IDirectSoundBuffer_Unlock(This->dsbuffer, buf1, size1, buf2, size2);
        This->writepos = (writepos + size1 + size2) % This->buf_size;
        TRACE("Wrote %u bytes at %u, next at %u - (%u/%u)\n", size1+size2, writepos, This->writepos, free, size);
        data += size1 + size2;
        size -= size1 + size2;
    }
    return S_OK;
}