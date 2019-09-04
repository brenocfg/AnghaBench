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
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IAudioRenderClient ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ CoMarshalInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ CoUnmarshalInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IAudioClient_GetMixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioRenderClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioRenderClient ; 
 scalar_t__ IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHCTX_INPROC ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ullZero ; 

__attribute__((used)) static void test_marshal(void)
{
    IStream *pStream;
    IAudioClient *ac, *acDest;
    IAudioRenderClient *rc, *rcDest;
    WAVEFORMATEX *pwfx;
    HRESULT hr;

    /* IAudioRenderClient */
    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED, 0, 5000000,
            0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    CoTaskMemFree(pwfx);

    hr = IAudioClient_GetService(ac, &IID_IAudioRenderClient, (void**)&rc);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);
    if(hr != S_OK) {
        IAudioClient_Release(ac);
        return;
    }

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    ok(hr == S_OK, "CreateStreamOnHGlobal failed 0x%08x\n", hr);

    /* marshal IAudioClient */

    hr = CoMarshalInterface(pStream, &IID_IAudioClient, (IUnknown*)ac, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    ok(hr == S_OK, "CoMarshalInterface IAudioClient failed 0x%08x\n", hr);

    IStream_Seek(pStream, ullZero, STREAM_SEEK_SET, NULL);
    hr = CoUnmarshalInterface(pStream, &IID_IAudioClient, (void **)&acDest);
    ok(hr == S_OK, "CoUnmarshalInterface IAudioClient failed 0x%08x\n", hr);
    if (hr == S_OK)
        IAudioClient_Release(acDest);

    IStream_Seek(pStream, ullZero, STREAM_SEEK_SET, NULL);
    /* marshal IAudioRenderClient */

    hr = CoMarshalInterface(pStream, &IID_IAudioRenderClient, (IUnknown*)rc, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    ok(hr == S_OK, "CoMarshalInterface IAudioRenderClient failed 0x%08x\n", hr);

    IStream_Seek(pStream, ullZero, STREAM_SEEK_SET, NULL);
    hr = CoUnmarshalInterface(pStream, &IID_IAudioRenderClient, (void **)&rcDest);
    ok(hr == S_OK, "CoUnmarshalInterface IAudioRenderClient failed 0x%08x\n", hr);
    if (hr == S_OK)
        IAudioRenderClient_Release(rcDest);


    IStream_Release(pStream);

    IAudioClient_Release(ac);
    IAudioRenderClient_Release(rc);

}