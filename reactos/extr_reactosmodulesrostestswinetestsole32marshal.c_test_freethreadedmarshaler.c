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
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IMarshal ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_InProcFreeMarshaler ; 
 int /*<<< orphan*/  CLSID_StdMarshal ; 
 int /*<<< orphan*/  CoCreateFreeThreadedMarshaler (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  CoReleaseMarshalData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IMarshal ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMarshal_DisconnectObject (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IMarshal_GetUnmarshalClass (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IMarshal_MarshalInterface (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IMarshal_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMarshal_ReleaseMarshalData (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IMarshal_UnmarshalInterface (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHCTX_INPROC ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  MSHLFLAGS_TABLESTRONG ; 
 int /*<<< orphan*/  MSHLFLAGS_TABLEWEAK ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Test_ClassFactory ; 
 scalar_t__ cLocks ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_more_than_one_lock () ; 
 int /*<<< orphan*/  ok_no_locks () ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  test_freethreadedmarshaldata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_freethreadedmarshaler(void)
{
    HRESULT hr;
    IUnknown *pFTUnknown;
    IMarshal *pFTMarshal;
    IStream *pStream;
    IUnknown *pProxy;
    static const LARGE_INTEGER llZero;
    CLSID clsid;

    cLocks = 0;
    hr = CoCreateFreeThreadedMarshaler(NULL, &pFTUnknown);
    ok_ole_success(hr, CoCreateFreeThreadedMarshaler);
    hr = IUnknown_QueryInterface(pFTUnknown, &IID_IMarshal, (void **)&pFTMarshal);
    ok_ole_success(hr, IUnknown_QueryInterface);
    IUnknown_Release(pFTUnknown);

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    ok_ole_success(hr, CreateStreamOnHGlobal);

    /* inproc normal marshaling */

    hr = IMarshal_GetUnmarshalClass(pFTMarshal, &IID_IClassFactory,
            &Test_ClassFactory, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL, &clsid);
    ok_ole_success(hr, IMarshal_GetUnmarshalClass);
    ok(IsEqualIID(&clsid, &CLSID_InProcFreeMarshaler), "clsid = %s\n",
            wine_dbgstr_guid(&clsid));

    hr = IMarshal_MarshalInterface(pFTMarshal, pStream, &IID_IClassFactory,
        &Test_ClassFactory, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    ok_ole_success(hr, IMarshal_MarshalInterface);

    ok_more_than_one_lock();

    test_freethreadedmarshaldata(pStream, MSHCTX_INPROC, &Test_ClassFactory, MSHLFLAGS_NORMAL);

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_UnmarshalInterface(pFTMarshal, pStream, &IID_IUnknown, (void **)&pProxy);
    ok_ole_success(hr, IMarshal_UnmarshalInterface);

    IUnknown_Release(pProxy);

    ok_no_locks();

    /* inproc table-strong marshaling */

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_MarshalInterface(pFTMarshal, pStream, &IID_IClassFactory,
        (IUnknown*)&Test_ClassFactory, MSHCTX_INPROC, (void *)0xdeadbeef,
        MSHLFLAGS_TABLESTRONG);
    ok_ole_success(hr, IMarshal_MarshalInterface);

    ok_more_than_one_lock();

    test_freethreadedmarshaldata(pStream, MSHCTX_INPROC, &Test_ClassFactory, MSHLFLAGS_TABLESTRONG);

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_UnmarshalInterface(pFTMarshal, pStream, &IID_IUnknown, (void **)&pProxy);
    ok_ole_success(hr, IMarshal_UnmarshalInterface);

    IUnknown_Release(pProxy);

    ok_more_than_one_lock();

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_ReleaseMarshalData(pFTMarshal, pStream);
    ok_ole_success(hr, IMarshal_ReleaseMarshalData);

    ok_no_locks();

    /* inproc table-weak marshaling */

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_MarshalInterface(pFTMarshal, pStream, &IID_IClassFactory,
        (IUnknown*)&Test_ClassFactory, MSHCTX_INPROC, (void *)0xdeadbeef,
        MSHLFLAGS_TABLEWEAK);
    ok_ole_success(hr, IMarshal_MarshalInterface);

    ok_no_locks();

    test_freethreadedmarshaldata(pStream, MSHCTX_INPROC, &Test_ClassFactory, MSHLFLAGS_TABLEWEAK);

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_UnmarshalInterface(pFTMarshal, pStream, &IID_IUnknown, (void **)&pProxy);
    ok_ole_success(hr, IMarshal_UnmarshalInterface);

    ok_more_than_one_lock();

    IUnknown_Release(pProxy);

    ok_no_locks();

    /* inproc normal marshaling (for extraordinary cases) */

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_MarshalInterface(pFTMarshal, pStream, &IID_IClassFactory,
        &Test_ClassFactory, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    ok_ole_success(hr, IMarshal_MarshalInterface);

    ok_more_than_one_lock();

    /* this call shows that DisconnectObject does nothing */
    hr = IMarshal_DisconnectObject(pFTMarshal, 0);
    ok_ole_success(hr, IMarshal_DisconnectObject);

    ok_more_than_one_lock();

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_ReleaseMarshalData(pFTMarshal, pStream);
    ok_ole_success(hr, IMarshal_ReleaseMarshalData);

    ok_no_locks();

    /* doesn't enforce marshaling rules here and allows us to unmarshal the
     * interface, even though it was freed above */
    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_UnmarshalInterface(pFTMarshal, pStream, &IID_IUnknown, (void **)&pProxy);
    ok_ole_success(hr, IMarshal_UnmarshalInterface);

    ok_no_locks();

    /* local normal marshaling */

    hr = IMarshal_GetUnmarshalClass(pFTMarshal, &IID_IClassFactory,
            &Test_ClassFactory, MSHCTX_LOCAL, NULL, MSHLFLAGS_NORMAL, &clsid);
    ok_ole_success(hr, IMarshal_GetUnmarshalClass);
    ok(IsEqualIID(&clsid, &CLSID_StdMarshal), "clsid = %s\n",
            wine_dbgstr_guid(&clsid));

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = IMarshal_MarshalInterface(pFTMarshal, pStream, &IID_IClassFactory, &Test_ClassFactory, MSHCTX_LOCAL, NULL, MSHLFLAGS_NORMAL);
    ok_ole_success(hr, IMarshal_MarshalInterface);

    ok_more_than_one_lock();

    test_freethreadedmarshaldata(pStream, MSHCTX_LOCAL, &Test_ClassFactory, MSHLFLAGS_NORMAL);

    IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    hr = CoReleaseMarshalData(pStream);
    ok_ole_success(hr, CoReleaseMarshalData);

    ok_no_locks();

    IStream_Release(pStream);
    IMarshal_Release(pFTMarshal);
}