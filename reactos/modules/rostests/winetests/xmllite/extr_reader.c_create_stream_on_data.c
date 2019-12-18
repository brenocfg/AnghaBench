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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GHND ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,unsigned int) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IStream *create_stream_on_data(const void *data, unsigned int size)
{
    IStream *stream = NULL;
    HGLOBAL hglobal;
    void *ptr;
    HRESULT hr;

    hglobal = GlobalAlloc(GHND, size);
    ptr = GlobalLock(hglobal);

    memcpy(ptr, data, size);

    hr = CreateStreamOnHGlobal(hglobal, TRUE, &stream);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(stream != NULL, "Expected non-NULL stream\n");

    GlobalUnlock(hglobal);

    return stream;
}