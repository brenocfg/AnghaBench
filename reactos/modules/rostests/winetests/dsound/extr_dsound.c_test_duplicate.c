#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event ;
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_11__ {int nAvgBytesPerSec; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
struct TYPE_13__ {void* hEventNotify; void* dwOffset; } ;
struct TYPE_12__ {int dwSize; int dwFlags; int dwBufferBytes; TYPE_1__* lpwfxFormat; } ;
typedef  TYPE_2__* LPVOID ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDNOTIFY ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND ;
typedef  scalar_t__ HRESULT ;
typedef  void* HANDLE ;
typedef  int DWORD ;
typedef  TYPE_2__ DSBUFFERDESC ;
typedef  TYPE_4__ DSBPOSITIONNOTIFY ;

/* Variables and functions */
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DSBCAPS_CTRLPOSITIONNOTIFY ; 
 int DSBCAPS_GETCURRENTPOSITION2 ; 
 int DSBCAPS_PRIMARYBUFFER ; 
 int /*<<< orphan*/  DSBLOCK_ENTIREBUFFER ; 
 void* DSBPN_OFFSETSTOP ; 
 scalar_t__ DSERR_ALLOCATED ; 
 scalar_t__ DSERR_GENERIC ; 
 scalar_t__ DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_NORMAL ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDirectSoundBuffer_Lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundBuffer_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundBuffer_Unlock (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IDirectSoundNotify_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundNotify_SetNotificationPositions (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 scalar_t__ IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_DuplicateSoundBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirectSound_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirectSoundNotify ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  init_format (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 scalar_t__ pDirectSoundCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_notify (int /*<<< orphan*/ *,int,void**,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static HRESULT test_duplicate(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND dso=NULL;
    LPDIRECTSOUNDBUFFER primary=NULL;
    DSBUFFERDESC bufdesc;
    int ref;

    /* Create the DirectSound object */
    rc=pDirectSoundCreate(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED,
       "DirectSoundCreate() failed: %08x\n",rc);
    if (rc!=DS_OK)
        return rc;

    /* We must call SetCooperativeLevel before creating primary buffer */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_PRIORITY */
    rc=IDirectSound_SetCooperativeLevel(dso,get_hwnd(),DSSCL_PRIORITY);
    ok(rc==DS_OK,"IDirectSound_SetCooperativeLevel() failed: %08x\n", rc);
    if (rc!=DS_OK)
        goto EXIT;

    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize=sizeof(bufdesc);
    bufdesc.dwFlags=DSBCAPS_PRIMARYBUFFER;
    rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&primary,NULL);
    ok(rc==DS_OK && primary!=NULL,"IDirectSound_CreateSoundBuffer() failed "
       "to create a primary buffer %08x\n",rc);

    if (rc==DS_OK && primary!=NULL) {
        LPDIRECTSOUNDBUFFER original=NULL;
        WAVEFORMATEX wfx;

        init_format(&wfx,WAVE_FORMAT_PCM,22050,16,1);
        ZeroMemory(&bufdesc, sizeof(bufdesc));
        bufdesc.dwSize=sizeof(bufdesc);
        bufdesc.dwFlags=DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_CTRLPOSITIONNOTIFY;
        bufdesc.dwBufferBytes=wfx.nAvgBytesPerSec/100; /* very short buffer */
        bufdesc.lpwfxFormat=&wfx;
        rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&original,NULL);
        ok(rc==DS_OK && original!=NULL,
           "IDirectSound_CreateSoundBuffer() failed to create a original "
           "buffer %08x\n",rc);
        if (rc==DS_OK && original!=NULL) {
            LPDIRECTSOUNDBUFFER duplicated=NULL;
            LPDIRECTSOUNDNOTIFY notify=NULL;
            HANDLE event[2];
            LPVOID buf=NULL;
            DWORD bufsize;
            int i;

            /* Prepare notify events */
            for (i=0;i<sizeof(event)/sizeof(event[0]);i++) {
                event[i] = CreateEvent(NULL,FALSE,FALSE,NULL);
            }

            /* Make silent buffer */
            rc=IDirectSoundBuffer_Lock(original,0,0,&buf,&bufsize,
                                       NULL,NULL,DSBLOCK_ENTIREBUFFER);
            ok(rc==DS_OK && buf!=NULL,
               "IDirectSoundBuffer_Lock failed to lock the buffer %08x\n",rc);
            if (rc==DS_OK && buf!=NULL) {
                ZeroMemory(buf,bufsize);
                rc=IDirectSoundBuffer_Unlock(original,buf,bufsize,
                                             NULL,0);
                ok(rc==DS_OK,"IDirectSoundBuffer_Unlock failed to unlock "
                   "%08x\n",rc);
            }

            rc=IDirectSoundBuffer_QueryInterface(original,
                                                 &IID_IDirectSoundNotify,
                                                 (void**)&notify);
            ok(rc==DS_OK && notify!=NULL,
               "IDirectSoundBuffer_QueryInterface() failed to create a "
               "notification %08x\n",rc);
            if (rc==DS_OK && notify!=NULL) {
                DSBPOSITIONNOTIFY dsbpn;
                LPDIRECTSOUNDNOTIFY dup_notify=NULL;

                dsbpn.dwOffset=DSBPN_OFFSETSTOP;
                dsbpn.hEventNotify=event[0];
                rc=IDirectSoundNotify_SetNotificationPositions(notify,
                                                               1,&dsbpn);
                ok(rc==DS_OK,"IDirectSoundNotify_SetNotificationPositions "
                   "failed %08x\n",rc);

                rc=IDirectSound_DuplicateSoundBuffer(dso,original,&duplicated);
                ok(rc==DS_OK && duplicated!=NULL,
                   "IDirectSound_DuplicateSoundBuffer failed %08x\n",rc);

                trace("testing duplicated buffer without notifications.\n");
                test_notify(duplicated,sizeof(event)/sizeof(event[0]),
                            event,WAIT_TIMEOUT);

                rc=IDirectSoundBuffer_QueryInterface(duplicated,
                                                     &IID_IDirectSoundNotify,
                                                     (void**)&dup_notify);
                ok(rc==DS_OK&&dup_notify!=NULL,
                   "IDirectSoundBuffer_QueryInterface() failed to create a "
                   "notification %08x\n",rc);
                if(rc==DS_OK&&dup_notify!=NULL) {
                    dsbpn.dwOffset=DSBPN_OFFSETSTOP;
                    dsbpn.hEventNotify=event[1];
                    rc=IDirectSoundNotify_SetNotificationPositions(dup_notify,
                                                                   1,&dsbpn);
                    ok(rc==DS_OK,"IDirectSoundNotify_SetNotificationPositions "
                       "failed %08x\n",rc);

                    trace("testing duplicated buffer with a notification.\n");
                    test_notify(duplicated,sizeof(event)/sizeof(event[0]),
                                event,WAIT_OBJECT_0+1);

                    ref=IDirectSoundNotify_Release(dup_notify);
                    ok(ref==0,"IDirectSoundNotify_Release() has %d references, "
                       "should have 0\n",ref);
                }
                ref=IDirectSoundNotify_Release(notify);
                ok(ref==0,"IDirectSoundNotify_Release() has %d references, "
                   "should have 0\n",ref);

                trace("testing original buffer with a notification.\n");
                test_notify(original,sizeof(event)/sizeof(event[0]),
                            event,WAIT_OBJECT_0);

                ref=IDirectSoundBuffer_Release(duplicated);
                ok(ref==0,"IDirectSoundBuffer_Release() has %d references, "
                   "should have 0\n",ref);
            }
            ref=IDirectSoundBuffer_Release(original);
            ok(ref==0,"IDirectSoundBuffer_Release() has %d references, "
               "should have 0\n",ref);
        }
        ref=IDirectSoundBuffer_Release(primary);
        ok(ref==0,"IDirectSoundBuffer_Release() has %d references, "
           "should have 0\n",ref);
    }

    /* Set the CooperativeLevel back to normal */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_NORMAL */
    rc=IDirectSound_SetCooperativeLevel(dso,get_hwnd(),DSSCL_NORMAL);
    ok(rc==DS_OK,"IDirectSound_SetCooperativeLevel() failed: %08x\n", rc);

EXIT:
    ref=IDirectSound_Release(dso);
    ok(ref==0,"IDirectSound_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
        return DSERR_GENERIC;

    return rc;
}