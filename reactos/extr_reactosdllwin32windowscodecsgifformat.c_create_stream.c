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
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

__attribute__((used)) static IStream *create_stream(const void *data, int data_size)
{
    HRESULT hr;
    IStream *stream;
    HGLOBAL hdata;
    void *locked_data;

    hdata = GlobalAlloc(GMEM_MOVEABLE, data_size);
    if (!hdata) return NULL;

    locked_data = GlobalLock(hdata);
    memcpy(locked_data, data, data_size);
    GlobalUnlock(hdata);

    hr = CreateStreamOnHGlobal(hdata, TRUE, &stream);
    return FAILED(hr) ? NULL : stream;
}