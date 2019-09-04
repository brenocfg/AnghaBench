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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_MPEG1Splitter ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IUnknown *create_mpeg_splitter(void)
{
    IUnknown *mpeg_splitter = NULL;
    HRESULT result = CoCreateInstance(&CLSID_MPEG1Splitter, NULL, CLSCTX_INPROC_SERVER,
            &IID_IUnknown, (void **)&mpeg_splitter);
    ok(S_OK == result, "got 0x%08x\n", result);
    return mpeg_splitter;
}