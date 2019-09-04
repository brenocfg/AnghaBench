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
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  CoReleaseMarshalData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoUnmarshalInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * CreateWindowA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 scalar_t__ GetMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TestMsg_ClassFactory ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_host_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hwnd_app ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_more_than_one_lock () ; 
 int /*<<< orphan*/  ok_no_locks () ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**)) ; 
 int /*<<< orphan*/  start_host_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ullZero ; 

__attribute__((used)) static void test_call_from_message(void)
{
    MSG msg;
    IStream *pStream;
    HRESULT hr;
    IClassFactory *proxy;
    DWORD tid;
    HANDLE thread;
    IUnknown *object;

    hwnd_app = CreateWindowA("WineCOMTest", NULL, 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, 0);
    ok(hwnd_app != NULL, "Window creation failed\n");

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    ok_ole_success(hr, CreateStreamOnHGlobal);
    tid = start_host_object(pStream, &IID_IClassFactory, (IUnknown*)&TestMsg_ClassFactory, MSHLFLAGS_NORMAL, &thread);

    ok_more_than_one_lock();

    IStream_Seek(pStream, ullZero, STREAM_SEEK_SET, NULL);
    hr = CoUnmarshalInterface(pStream, &IID_IClassFactory, (void **)&proxy);
    ok_ole_success(hr, CoReleaseMarshalData);
    IStream_Release(pStream);

    ok_more_than_one_lock();

    /* start message re-entrancy test */
    hr = IClassFactory_CreateInstance(proxy, NULL, &IID_IUnknown, (void **)&object);
    ok_ole_success(hr, IClassFactory_CreateInstance);

    IClassFactory_Release(proxy);

    ok_no_locks();

    end_host_object(tid, thread);

    while (GetMessageA(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    DestroyWindow(hwnd_app);
}