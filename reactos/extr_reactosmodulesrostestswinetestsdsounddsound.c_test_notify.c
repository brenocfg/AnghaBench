#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LPHANDLE ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDirectSoundBuffer_Play (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundBuffer_SetCurrentPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundBuffer_Stop (int /*<<< orphan*/ ) ; 
 scalar_t__ WaitForMultipleObjects (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static HRESULT test_notify(LPDIRECTSOUNDBUFFER dsb,
                           DWORD count, LPHANDLE event,
                           DWORD expected)
{
    HRESULT rc;
    DWORD ret;

    rc=IDirectSoundBuffer_SetCurrentPosition(dsb,0);
    ok(rc==DS_OK,
       "IDirectSoundBuffer_SetCurrentPosition failed %08x\n",rc);
    if(rc!=DS_OK)
        return rc;

    rc=IDirectSoundBuffer_Play(dsb,0,0,0);
    ok(rc==DS_OK,"IDirectSoundBuffer_Play failed %08x\n",rc);
    if(rc!=DS_OK)
        return rc;

    rc=IDirectSoundBuffer_Stop(dsb);
    ok(rc==DS_OK,"IDirectSoundBuffer_Stop failed %08x\n",rc);
    if(rc!=DS_OK)
        return rc;

    ret=WaitForMultipleObjects(count,event,FALSE,0);
    ok(ret==expected,"expected %d. got %d\n",expected,ret);
    return rc;
}