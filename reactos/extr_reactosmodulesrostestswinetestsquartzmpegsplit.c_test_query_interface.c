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
typedef  int /*<<< orphan*/  IAMStreamSelect ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IAMStreamSelect_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAMStreamSelect ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_mpeg_splitter () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_query_interface(void)
{
    IUnknown *mpeg_splitter = create_mpeg_splitter();

    IAMStreamSelect *stream_select = NULL;
    HRESULT result = IUnknown_QueryInterface(
            mpeg_splitter, &IID_IAMStreamSelect, (void **)&stream_select);
    ok(S_OK == result, "got 0x%08x\n", result);
    if (S_OK == result)
    {
        IAMStreamSelect_Release(stream_select);
    }

    IUnknown_Release(mpeg_splitter);
}