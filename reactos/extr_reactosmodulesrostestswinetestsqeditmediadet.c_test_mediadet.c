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
struct TYPE_5__ {int /*<<< orphan*/ * member_0; } ;
struct unk_impl {int member_1; int ref; int /*<<< orphan*/  inner_unk; int /*<<< orphan*/  IUnknown_iface; int /*<<< orphan*/ * member_2; TYPE_1__ member_0; } ;
typedef  int ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  pbFormat; int /*<<< orphan*/  majortype; } ;
typedef  void* LPVOID ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IMediaDet ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;
typedef  TYPE_2__ AM_MEDIA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_MediaDet ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 int E_INVALIDARG ; 
 int E_POINTER ; 
 int /*<<< orphan*/  IID_IMediaDet ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IMediaDet_AddRef (int /*<<< orphan*/ *) ; 
 int IMediaDet_Release (int /*<<< orphan*/ *) ; 
 int IMediaDet_get_CurrentStream (int /*<<< orphan*/ *,int*) ; 
 int IMediaDet_get_Filename (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IMediaDet_get_FrameRate (int /*<<< orphan*/ *,double*) ; 
 int IMediaDet_get_OutputStreams (int /*<<< orphan*/ *,int*) ; 
 int IMediaDet_get_StreamMediaType (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int IMediaDet_put_CurrentStream (int /*<<< orphan*/ *,int) ; 
 int IMediaDet_put_Filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIATYPE_Audio ; 
 int /*<<< orphan*/  MEDIATYPE_Video ; 
 int S_OK ; 
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int VFW_E_INVALIDMEDIATYPE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_avi_filename ; 
 int /*<<< orphan*/  test_sound_avi_filename ; 
 int /*<<< orphan*/  unk_vtbl ; 

__attribute__((used)) static void test_mediadet(void)
{
    HRESULT hr;
    struct unk_impl unk_obj = {{&unk_vtbl}, 19, NULL};
    IMediaDet *pM = NULL;
    ULONG refcount;
    BSTR filename = NULL;
    LONG nstrms = 0;
    LONG strm;
    AM_MEDIA_TYPE mt;
    double fps;
    int flags;
    int i;

    /* COM aggregation */
    hr = CoCreateInstance(&CLSID_MediaDet, &unk_obj.IUnknown_iface, CLSCTX_INPROC_SERVER,
            &IID_IUnknown, (void**)&unk_obj.inner_unk);
    ok(hr == S_OK, "CoCreateInstance failed: %08x\n", hr);

    hr = IUnknown_QueryInterface(unk_obj.inner_unk, &IID_IMediaDet, (void**)&pM);
    ok(hr == S_OK, "QueryInterface for IID_IMediaDet failed: %08x\n", hr);
    refcount = IMediaDet_AddRef(pM);
    ok(refcount == unk_obj.ref, "MediaDet just pretends to support COM aggregation\n");
    refcount = IMediaDet_Release(pM);
    ok(refcount == unk_obj.ref, "MediaDet just pretends to support COM aggregation\n");
    refcount = IMediaDet_Release(pM);
    ok(refcount == 19, "Refcount should be back at 19 but is %u\n", refcount);

    IUnknown_Release(unk_obj.inner_unk);

    /* test.avi has one video stream.  */
    hr = CoCreateInstance(&CLSID_MediaDet, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMediaDet, (LPVOID*)&pM);
    ok(hr == S_OK, "CoCreateInstance failed with %x\n", hr);
    ok(pM != NULL, "pM is NULL\n");

    filename = NULL;
    hr = IMediaDet_get_Filename(pM, &filename);
    /* Despite what MSDN claims, this returns S_OK.  */
    ok(hr == S_OK, "IMediaDet_get_Filename failed: %08x\n", hr);
    ok(filename == NULL, "IMediaDet_get_Filename\n");

    filename = (BSTR) -1;
    hr = IMediaDet_get_Filename(pM, &filename);
    /* Despite what MSDN claims, this returns S_OK.  */
    ok(hr == S_OK, "IMediaDet_get_Filename failed: %08x\n", hr);
    ok(filename == NULL, "IMediaDet_get_Filename\n");

    nstrms = -1;
    hr = IMediaDet_get_OutputStreams(pM, &nstrms);
    ok(hr == E_INVALIDARG, "IMediaDet_get_OutputStreams failed: %08x\n", hr);
    ok(nstrms == -1, "IMediaDet_get_OutputStreams: nstrms is %i\n", nstrms);

    strm = -1;
    /* The stream defaults to 0, even without a file!  */
    hr = IMediaDet_get_CurrentStream(pM, &strm);
    ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
    ok(strm == 0, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

    hr = IMediaDet_get_CurrentStream(pM, NULL);
    ok(hr == E_POINTER, "IMediaDet_get_CurrentStream failed: %08x\n", hr);

    /* But put_CurrentStream doesn't.  */
    hr = IMediaDet_put_CurrentStream(pM, 0);
    ok(hr == E_INVALIDARG, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    hr = IMediaDet_put_CurrentStream(pM, -1);
    ok(hr == E_INVALIDARG, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    hr = IMediaDet_get_StreamMediaType(pM, &mt);
    ok(hr == E_INVALIDARG, "IMediaDet_get_StreamMediaType failed: %08x\n", hr);

    hr = IMediaDet_get_StreamMediaType(pM, NULL);
    ok(hr == E_POINTER, "IMediaDet_get_StreamMediaType failed: %08x\n", hr);

    filename = SysAllocString(test_avi_filename);
    hr = IMediaDet_put_Filename(pM, filename);
    ok(hr == S_OK, "IMediaDet_put_Filename failed: %08x\n", hr);
    SysFreeString(filename);

    strm = -1;
    /* The stream defaults to 0.  */
    hr = IMediaDet_get_CurrentStream(pM, &strm);
    ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
    ok(strm == 0, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

    ZeroMemory(&mt, sizeof mt);
    hr = IMediaDet_get_StreamMediaType(pM, &mt);
    ok(hr == S_OK, "IMediaDet_get_StreamMediaType failed: %08x\n", hr);
    CoTaskMemFree(mt.pbFormat);

    /* Even before get_OutputStreams.  */
    hr = IMediaDet_put_CurrentStream(pM, 1);
    ok(hr == E_INVALIDARG, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    hr = IMediaDet_get_OutputStreams(pM, &nstrms);
    ok(hr == S_OK, "IMediaDet_get_OutputStreams failed: %08x\n", hr);
    ok(nstrms == 1, "IMediaDet_get_OutputStreams: nstrms is %i\n", nstrms);

    filename = NULL;
    hr = IMediaDet_get_Filename(pM, &filename);
    ok(hr == S_OK, "IMediaDet_get_Filename failed: %08x\n", hr);
    ok(lstrcmpW(filename, test_avi_filename) == 0,
       "IMediaDet_get_Filename\n");
    SysFreeString(filename);

    hr = IMediaDet_get_Filename(pM, NULL);
    ok(hr == E_POINTER, "IMediaDet_get_Filename failed: %08x\n", hr);

    strm = -1;
    hr = IMediaDet_get_CurrentStream(pM, &strm);
    ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
    ok(strm == 0, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

    hr = IMediaDet_get_CurrentStream(pM, NULL);
    ok(hr == E_POINTER, "IMediaDet_get_CurrentStream failed: %08x\n", hr);

    hr = IMediaDet_put_CurrentStream(pM, -1);
    ok(hr == E_INVALIDARG, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    hr = IMediaDet_put_CurrentStream(pM, 1);
    ok(hr == E_INVALIDARG, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    /* Try again.  */
    strm = -1;
    hr = IMediaDet_get_CurrentStream(pM, &strm);
    ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
    ok(strm == 0, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

    hr = IMediaDet_put_CurrentStream(pM, 0);
    ok(hr == S_OK, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    strm = -1;
    hr = IMediaDet_get_CurrentStream(pM, &strm);
    ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
    ok(strm == 0, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

    ZeroMemory(&mt, sizeof mt);
    hr = IMediaDet_get_StreamMediaType(pM, &mt);
    ok(hr == S_OK, "IMediaDet_get_StreamMediaType failed: %08x\n", hr);
    ok(IsEqualGUID(&mt.majortype, &MEDIATYPE_Video),
                 "IMediaDet_get_StreamMediaType\n");
    CoTaskMemFree(mt.pbFormat);

    hr = IMediaDet_get_FrameRate(pM, NULL);
    ok(hr == E_POINTER, "IMediaDet_get_FrameRate failed: %08x\n", hr);

    hr = IMediaDet_get_FrameRate(pM, &fps);
    ok(hr == S_OK, "IMediaDet_get_FrameRate failed: %08x\n", hr);
    ok(fps == 10.0, "IMediaDet_get_FrameRate: fps is %f\n", fps);

    hr = IMediaDet_Release(pM);
    ok(hr == 0, "IMediaDet_Release returned: %x\n", hr);

    DeleteFileW(test_avi_filename);

    /* test_sound.avi has one video stream and one audio stream.  */
    hr = CoCreateInstance(&CLSID_MediaDet, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMediaDet, (LPVOID*)&pM);
    ok(hr == S_OK, "CoCreateInstance failed with %x\n", hr);
    ok(pM != NULL, "pM is NULL\n");

    filename = SysAllocString(test_sound_avi_filename);
    hr = IMediaDet_put_Filename(pM, filename);
    ok(hr == S_OK, "IMediaDet_put_Filename failed: %08x\n", hr);
    SysFreeString(filename);

    hr = IMediaDet_get_OutputStreams(pM, &nstrms);
    ok(hr == S_OK, "IMediaDet_get_OutputStreams failed: %08x\n", hr);
    ok(nstrms == 2, "IMediaDet_get_OutputStreams: nstrms is %i\n", nstrms);

    filename = NULL;
    hr = IMediaDet_get_Filename(pM, &filename);
    ok(hr == S_OK, "IMediaDet_get_Filename failed: %08x\n", hr);
    ok(lstrcmpW(filename, test_sound_avi_filename) == 0,
       "IMediaDet_get_Filename\n");
    SysFreeString(filename);

    /* I don't know if the stream order is deterministic.  Just check
       for both an audio and video stream.  */
    flags = 0;

    for (i = 0; i < 2; ++i)
    {
        hr = IMediaDet_put_CurrentStream(pM, i);
        ok(hr == S_OK, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

        strm = -1;
        hr = IMediaDet_get_CurrentStream(pM, &strm);
        ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
        ok(strm == i, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

        ZeroMemory(&mt, sizeof mt);
        hr = IMediaDet_get_StreamMediaType(pM, &mt);
        ok(hr == S_OK, "IMediaDet_get_StreamMediaType failed: %08x\n", hr);
        flags += (IsEqualGUID(&mt.majortype, &MEDIATYPE_Video)
                  ? 1
                  : (IsEqualGUID(&mt.majortype, &MEDIATYPE_Audio)
                     ? 2
                     : 0));

        if (IsEqualGUID(&mt.majortype, &MEDIATYPE_Audio))
        {
            hr = IMediaDet_get_FrameRate(pM, &fps);
            ok(hr == VFW_E_INVALIDMEDIATYPE, "IMediaDet_get_FrameRate failed: %08x\n", hr);
        }

        CoTaskMemFree(mt.pbFormat);
    }
    ok(flags == 3, "IMediaDet_get_StreamMediaType: flags are %i\n", flags);

    hr = IMediaDet_put_CurrentStream(pM, 2);
    ok(hr == E_INVALIDARG, "IMediaDet_put_CurrentStream failed: %08x\n", hr);

    strm = -1;
    hr = IMediaDet_get_CurrentStream(pM, &strm);
    ok(hr == S_OK, "IMediaDet_get_CurrentStream failed: %08x\n", hr);
    ok(strm == 1, "IMediaDet_get_CurrentStream: strm is %i\n", strm);

    hr = IMediaDet_Release(pM);
    ok(hr == 0, "IMediaDet_Release returned: %x\n", hr);

    DeleteFileW(test_sound_avi_filename);
}