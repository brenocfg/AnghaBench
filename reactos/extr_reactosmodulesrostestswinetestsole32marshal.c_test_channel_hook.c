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
struct host_object_data {int /*<<< orphan*/  stream; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CoRegisterChannelHook (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoRegisterMessageFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUnmarshalInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  EXTENTID_WineTest ; 
 int /*<<< orphan*/  IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  MessageFilter ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TestChannelHook ; 
 int /*<<< orphan*/  Test_ClassFactory ; 
 scalar_t__ cLocks ; 
 int /*<<< orphan*/  end_host_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int method ; 
 int /*<<< orphan*/  ok_more_than_one_lock () ; 
 int /*<<< orphan*/  ok_no_locks () ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  server_tid ; 
 int /*<<< orphan*/  start_host_object2 (struct host_object_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ullZero ; 

__attribute__((used)) static void test_channel_hook(void)
{
    IClassFactory *cf = NULL;
    DWORD tid;
    IUnknown *proxy = NULL;
    HANDLE thread;
    HRESULT hr;

    struct host_object_data object_data = { NULL, &IID_IClassFactory, (IUnknown*)&Test_ClassFactory,
                                            MSHLFLAGS_NORMAL, &MessageFilter };

    hr = CoRegisterChannelHook(&EXTENTID_WineTest, &TestChannelHook);
    ok_ole_success(hr, CoRegisterChannelHook);

    hr = CoRegisterMessageFilter(&MessageFilter, NULL);
    ok_ole_success(hr, CoRegisterMessageFilter);

    cLocks = 0;

    hr = CreateStreamOnHGlobal(NULL, TRUE, &object_data.stream);
    ok_ole_success(hr, CreateStreamOnHGlobal);
    tid = start_host_object2(&object_data, &thread);
    server_tid = tid;

    ok_more_than_one_lock();

    IStream_Seek(object_data.stream, ullZero, STREAM_SEEK_SET, NULL);
    hr = CoUnmarshalInterface(object_data.stream, &IID_IClassFactory, (void **)&cf);
    ok_ole_success(hr, CoUnmarshalInterface);
    IStream_Release(object_data.stream);

    ok_more_than_one_lock();

    method = 3;
    hr = IClassFactory_CreateInstance(cf, NULL, &IID_IUnknown, (LPVOID*)&proxy);
    ok_ole_success(hr, IClassFactory_CreateInstance);

    method = 5;
    IUnknown_Release(proxy);

    IClassFactory_Release(cf);

    ok_no_locks();

    end_host_object(tid, thread);

    hr = CoRegisterMessageFilter(NULL, NULL);
    ok_ole_success(hr, CoRegisterMessageFilter);
}