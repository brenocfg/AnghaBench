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
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND8 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DSERR_ALLOCATED ; 
 scalar_t__ DSERR_GENERIC ; 
 scalar_t__ DSERR_NODRIVER ; 
 scalar_t__ DS_OK ; 
 scalar_t__ E_FAIL ; 
 int IDirectSound8_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 scalar_t__ pDirectSoundCreate8 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT test_for_driver8(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND8 dso=NULL;
    int ref;

    /* Create the DirectSound object */
    rc=pDirectSoundCreate8(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL,
       "DirectSoundCreate8() failed: %08x\n",rc);
    if (rc!=DS_OK)
        return rc;

    ref=IDirectSound8_Release(dso);
    ok(ref==0,"IDirectSound8_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
        return DSERR_GENERIC;

    return rc;
}