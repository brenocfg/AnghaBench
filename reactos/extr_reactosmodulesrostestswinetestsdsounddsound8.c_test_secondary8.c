#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wfxe ;
typedef  int /*<<< orphan*/  wfx1 ;
typedef  int /*<<< orphan*/  wfx ;
typedef  int /*<<< orphan*/  dscaps ;
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_14__ {int nAvgBytesPerSec; int wBitsPerSample; int cbSize; int nChannels; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  wFormatTag; int /*<<< orphan*/  nBlockAlign; } ;
struct TYPE_12__ {int wValidBitsPerSample; } ;
struct TYPE_13__ {TYPE_3__ Format; TYPE_1__ Samples; void* SubFormat; int /*<<< orphan*/  dwChannelMask; } ;
typedef  TYPE_2__ WAVEFORMATEXTENSIBLE ;
typedef  TYPE_3__ WAVEFORMATEX ;
struct TYPE_15__ {int dwSize; TYPE_3__* lpwfxFormat; void* dwBufferBytes; void* dwFlags; } ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND8 ;
typedef  int HRESULT ;
typedef  size_t DWORD ;
typedef  TYPE_4__ DSCAPS ;
typedef  TYPE_4__ DSBUFFERDESC ;

/* Variables and functions */
 int BUFFER_LEN ; 
 void* DSBCAPS_GETCURRENTPOSITION2 ; 
 void* DSBCAPS_PRIMARYBUFFER ; 
 int DSERR_ALLOCATED ; 
 int DSERR_CONTROLUNAVAIL ; 
 int DSERR_GENERIC ; 
 int DSERR_INVALIDCALL ; 
 int DSERR_INVALIDPARAM ; 
 int DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_NORMAL ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 int DS_OK ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 void* GUID_NULL ; 
 int IDirectSound8_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int IDirectSound8_GetCaps (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int IDirectSound8_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound8_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSoundBuffer_GetFormat (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSAUDIO_SPEAKER_MONO ; 
 int /*<<< orphan*/  KSAUDIO_SPEAKER_STEREO ; 
 void* KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 void* KSDATAFORMAT_SUBTYPE_PCM ; 
 size_t NB_FORMATS ; 
 size_t NB_TAGS ; 
 int /*<<< orphan*/  WAVE_FORMAT_EXTENSIBLE ; 
 scalar_t__ WAVE_FORMAT_IEEE_FLOAT ; 
 scalar_t__ WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 
 void* align (int,int /*<<< orphan*/ ) ; 
 scalar_t__* format_tags ; 
 int** formats ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  init_format (TYPE_3__*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pDirectSoundCreate8 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_buffer8 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HRESULT test_secondary8(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND8 dso=NULL;
    LPDIRECTSOUNDBUFFER primary=NULL,secondary=NULL;
    DSBUFFERDESC bufdesc;
    DSCAPS dscaps;
    WAVEFORMATEX wfx, wfx1;
    DWORD f, tag;
    int ref;

    /* Create the DirectSound object */
    rc=pDirectSoundCreate8(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED,
       "DirectSoundCreate8() failed: %08x\n",rc);
    if (rc!=DS_OK)
        return rc;

    /* Get the device capabilities */
    ZeroMemory(&dscaps, sizeof(dscaps));
    dscaps.dwSize=sizeof(dscaps);
    rc=IDirectSound8_GetCaps(dso,&dscaps);
    ok(rc==DS_OK,"IDirectSound8_GetCaps() failed: %08x\n",rc);
    if (rc!=DS_OK)
        goto EXIT;

    /* We must call SetCooperativeLevel before creating primary buffer */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_PRIORITY */
    rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_PRIORITY);
    ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel() failed: %08x\n", rc);
    if (rc!=DS_OK)
        goto EXIT;

    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize=sizeof(bufdesc);
    bufdesc.dwFlags=DSBCAPS_PRIMARYBUFFER;
    rc=IDirectSound8_CreateSoundBuffer(dso,&bufdesc,&primary,NULL);
    ok(rc==DS_OK && primary!=NULL,
       "IDirectSound8_CreateSoundBuffer() failed to create a primary buffer "
       "%08x\n",rc);

    if (rc==DS_OK && primary!=NULL) {
        rc=IDirectSoundBuffer_GetFormat(primary,&wfx1,sizeof(wfx1),NULL);
        ok(rc==DS_OK,"IDirectSoundBuffer8_Getformat() failed: %08x\n", rc);
        if (rc!=DS_OK)
            goto EXIT1;

        for (f=0;f<NB_FORMATS;f++) {
          for (tag=0;tag<NB_TAGS;tag++) {
            WAVEFORMATEXTENSIBLE wfxe;

            /* if float, we only want to test 32-bit */
            if ((format_tags[tag] == WAVE_FORMAT_IEEE_FLOAT) && (formats[f][1] != 32))
                continue;

            init_format(&wfx,format_tags[tag],formats[f][0],formats[f][1],
                        formats[f][2]);
            secondary=NULL;
            ZeroMemory(&bufdesc, sizeof(bufdesc));
            bufdesc.dwSize=sizeof(bufdesc);
            bufdesc.dwFlags=DSBCAPS_GETCURRENTPOSITION2;
            bufdesc.dwBufferBytes=align(wfx.nAvgBytesPerSec*BUFFER_LEN/1000,
                                        wfx.nBlockAlign);
            rc=IDirectSound8_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DSERR_INVALIDPARAM,"IDirectSound8_CreateSoundBuffer() "
               "should have returned DSERR_INVALIDPARAM, returned: %08x\n", rc);
            if (rc==DS_OK && secondary!=NULL)
                IDirectSoundBuffer_Release(secondary);

            secondary=NULL;
            ZeroMemory(&bufdesc, sizeof(bufdesc));
            bufdesc.dwSize=sizeof(bufdesc);
            bufdesc.dwFlags=DSBCAPS_GETCURRENTPOSITION2;
            bufdesc.dwBufferBytes=align(wfx.nAvgBytesPerSec*BUFFER_LEN/1000,
                                        wfx.nBlockAlign);
            bufdesc.lpwfxFormat=&wfx;
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            if (wfx.wBitsPerSample != 8 && wfx.wBitsPerSample != 16)
                ok(((rc == DSERR_CONTROLUNAVAIL || rc == DSERR_INVALIDCALL || rc == DSERR_INVALIDPARAM /* 2003 */) && !secondary)
                    || rc == DS_OK, /* driver dependent? */
                    "IDirectSound_CreateSoundBuffer() "
                    "should have returned (DSERR_CONTROLUNAVAIL or DSERR_INVALIDCALL) "
                    "and NULL, returned: %08x %p\n", rc, secondary);
            else
                ok(rc==DS_OK && secondary!=NULL,
                    "IDirectSound_CreateSoundBuffer() failed to create a secondary "
                    "buffer %08x\n",rc);
            if (secondary)
                IDirectSoundBuffer_Release(secondary);
            secondary = NULL;

            bufdesc.lpwfxFormat=(WAVEFORMATEX*)&wfxe;
            wfxe.Format = wfx;
            wfxe.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
            wfxe.SubFormat = (format_tags[tag] == WAVE_FORMAT_PCM ? KSDATAFORMAT_SUBTYPE_PCM : KSDATAFORMAT_SUBTYPE_IEEE_FLOAT);
            wfxe.Format.cbSize = 1;
            wfxe.Samples.wValidBitsPerSample = wfx.wBitsPerSample;
            wfxe.dwChannelMask = (wfx.nChannels == 1 ? KSAUDIO_SPEAKER_MONO : KSAUDIO_SPEAKER_STEREO);

            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DSERR_INVALIDPARAM && !secondary,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }

            wfxe.Format.cbSize = sizeof(wfxe) - sizeof(wfx) + 1;

            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(((rc==DSERR_CONTROLUNAVAIL || rc==DSERR_INVALIDCALL /* 2003 */) && !secondary)
                || rc==DS_OK /* driver dependent? */,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }

            wfxe.Format.cbSize = sizeof(wfxe) - sizeof(wfx);
            wfxe.SubFormat = GUID_NULL;
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok((rc==DSERR_INVALIDPARAM || rc==DSERR_INVALIDCALL) && !secondary,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }

            wfxe.Format.cbSize = sizeof(wfxe);
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok((rc==DSERR_CONTROLUNAVAIL || rc==DSERR_INVALIDCALL || rc==E_INVALIDARG) && !secondary,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }

            wfxe.SubFormat = (format_tags[tag] == WAVE_FORMAT_PCM ? KSDATAFORMAT_SUBTYPE_PCM : KSDATAFORMAT_SUBTYPE_IEEE_FLOAT);
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DS_OK && secondary,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }

            wfxe.Format.cbSize = sizeof(wfxe) + 1;
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(((rc==DSERR_CONTROLUNAVAIL || rc==DSERR_INVALIDCALL /* 2003 */) && !secondary)
                || rc==DS_OK /* driver dependent? */,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }

            wfxe.Format.cbSize = sizeof(wfxe) - sizeof(wfx);
            ++wfxe.Samples.wValidBitsPerSample;
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DSERR_INVALIDPARAM && !secondary,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }
            --wfxe.Samples.wValidBitsPerSample;

            wfxe.Samples.wValidBitsPerSample = 0;
            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DS_OK && secondary,
                "IDirectSound_CreateSoundBuffer() returned: %08x %p\n",
                rc, secondary);
            if (secondary)
            {
                IDirectSoundBuffer_Release(secondary);
                secondary=NULL;
            }
            wfxe.Samples.wValidBitsPerSample = wfxe.Format.wBitsPerSample;

            rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DS_OK && secondary!=NULL,
                "IDirectSound_CreateSoundBuffer() failed to create a secondary "
                "buffer %08x\n",rc);

            if (rc==DS_OK && secondary!=NULL) {
                if (winetest_interactive) {
                    trace("  Testing a secondary buffer at %dx%dx%d (fmt=%d) "
                        "with a primary buffer at %dx%dx%d\n",
                        wfx.nSamplesPerSec,wfx.wBitsPerSample,wfx.nChannels,format_tags[tag],
                        wfx1.nSamplesPerSec,wfx1.wBitsPerSample,wfx1.nChannels);
                }
                test_buffer8(dso,&secondary,0,FALSE,0,FALSE,0,
                             winetest_interactive,1.0,0,NULL,0,0);

                ref=IDirectSoundBuffer_Release(secondary);
                ok(ref==0,"IDirectSoundBuffer_Release() has %d references, "
                   "should have 0\n",ref);
            }
          }
        }
EXIT1:
        ref=IDirectSoundBuffer_Release(primary);
        ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, "
           "should have 0\n",ref);
    }

    /* Set the CooperativeLevel back to normal */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_NORMAL */
    rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_NORMAL);
    ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel() failed: %08x\n", rc);

EXIT:
    ref=IDirectSound8_Release(dso);
    ok(ref==0,"IDirectSound8_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
        return DSERR_GENERIC;

    return rc;
}