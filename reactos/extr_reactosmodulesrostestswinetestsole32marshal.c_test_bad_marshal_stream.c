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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CoMarshalInterface (int /*<<< orphan*/ *,...) ; 
 scalar_t__ CoReleaseMarshalData (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHCTX_INPROC ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 scalar_t__ STG_E_READFAULT ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Test_ClassFactory ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok_more_than_one_lock () ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,scalar_t__ (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  ullZero ; 

__attribute__((used)) static void test_bad_marshal_stream(void)
{
    HRESULT hr;
    IStream *pStream = NULL;

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    ok_ole_success(hr, CreateStreamOnHGlobal);
    hr = CoMarshalInterface(pStream, &IID_IClassFactory, (IUnknown*)&Test_ClassFactory, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    ok_ole_success(hr, CoMarshalInterface);

    ok_more_than_one_lock();

    /* try to read beyond end of stream */
    hr = CoReleaseMarshalData(pStream);
    ok(hr == STG_E_READFAULT, "Should have failed with STG_E_READFAULT, but returned 0x%08x instead\n", hr);

    /* now release for real */
    IStream_Seek(pStream, ullZero, STREAM_SEEK_SET, NULL);
    hr = CoReleaseMarshalData(pStream);
    ok_ole_success(hr, CoReleaseMarshalData);

    IStream_Release(pStream);
}