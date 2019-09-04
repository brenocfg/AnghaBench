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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMediaStream ;
typedef  int /*<<< orphan*/  IDirectDrawSurface ;
typedef  int /*<<< orphan*/  IDirectDrawStreamSample ;
typedef  int /*<<< orphan*/  IDirectDrawMediaStream ;
typedef  int /*<<< orphan*/  IAMMultiMediaStream ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AMMSF_ADDDEFAULTRENDERER ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAMMultiMediaStream_AddMediaStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAMMultiMediaStream_GetMediaStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IAMMultiMediaStream_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAMMultiMediaStream_OpenFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAMMultiMediaStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDirectDrawMediaStream_CreateSample (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirectDrawMediaStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDirectDrawStreamSample_GetSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDrawStreamSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDirectDrawSurface7_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirectDrawSurface_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectDrawMediaStream ; 
 int /*<<< orphan*/  IID_IDirectDrawSurface ; 
 int /*<<< orphan*/ * IMediaStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSPID_PrimaryAudio ; 
 int /*<<< orphan*/  MSPID_PrimaryVideo ; 
 int /*<<< orphan*/  STREAMTYPE_READ ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/ * create_ammultimediastream () ; 
 int /*<<< orphan*/  create_directdraw () ; 
 int /*<<< orphan*/  filenameW ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ pdd7 ; 
 int /*<<< orphan*/  pdds7 ; 
 int /*<<< orphan*/  release_directdraw () ; 

__attribute__((used)) static void test_renderfile(void)
{
    IAMMultiMediaStream *pams;
    HRESULT hr;
    IMediaStream *pvidstream = NULL;
    IDirectDrawMediaStream *pddstream = NULL;
    IDirectDrawStreamSample *pddsample = NULL;
    IDirectDrawSurface *surface;
    RECT rect;

    if (!(pams = create_ammultimediastream()))
        return;
    if (!create_directdraw())
    {
        IAMMultiMediaStream_Release(pams);
        return;
    }

    hr = IAMMultiMediaStream_Initialize(pams, STREAMTYPE_READ, 0, NULL);
    ok(hr==S_OK, "IAMMultiMediaStream_Initialize returned: %x\n", hr);

    hr = IAMMultiMediaStream_AddMediaStream(pams, (IUnknown*)pdd7, &MSPID_PrimaryVideo, 0, NULL);
    ok(hr==S_OK, "IAMMultiMediaStream_AddMediaStream returned: %x\n", hr);

    hr = IAMMultiMediaStream_AddMediaStream(pams, NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL);
    ok(hr==S_OK, "IAMMultiMediaStream_AddMediaStream returned: %x\n", hr);

    hr = IAMMultiMediaStream_OpenFile(pams, filenameW, 0);
    ok(hr==S_OK, "IAMMultiMediaStream_OpenFile returned: %x\n", hr);

    hr = IAMMultiMediaStream_GetMediaStream(pams, &MSPID_PrimaryVideo, &pvidstream);
    ok(hr==S_OK, "IAMMultiMediaStream_GetMediaStream returned: %x\n", hr);
    if (FAILED(hr)) goto error;

    hr = IMediaStream_QueryInterface(pvidstream, &IID_IDirectDrawMediaStream, (LPVOID*)&pddstream);
    ok(hr==S_OK, "IMediaStream_QueryInterface returned: %x\n", hr);
    if (FAILED(hr)) goto error;

    hr = IDirectDrawMediaStream_CreateSample(pddstream, NULL, NULL, 0, &pddsample);
    ok(hr == S_OK, "IDirectDrawMediaStream_CreateSample returned: %x\n", hr);

    surface = NULL;
    hr = IDirectDrawStreamSample_GetSurface(pddsample, &surface, &rect);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(surface == NULL, "got %p\n", surface);
    IDirectDrawStreamSample_Release(pddsample);

    hr = IDirectDrawSurface7_QueryInterface(pdds7, &IID_IDirectDrawSurface, (void**)&surface);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    EXPECT_REF(surface, 1);
    hr = IDirectDrawMediaStream_CreateSample(pddstream, surface, NULL, 0, &pddsample);
    ok(hr == S_OK, "IDirectDrawMediaStream_CreateSample returned: %x\n", hr);
    EXPECT_REF(surface, 2);
    IDirectDrawStreamSample_Release(pddsample);
    IDirectDrawSurface_Release(surface);

error:
    if (pddstream)
        IDirectDrawMediaStream_Release(pddstream);
    if (pvidstream)
        IMediaStream_Release(pvidstream);

    release_directdraw();
    IAMMultiMediaStream_Release(pams);
}