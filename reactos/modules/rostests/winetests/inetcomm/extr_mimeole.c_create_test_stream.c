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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IStream_iface; scalar_t__ pos; } ;
typedef  TYPE_1__ TestStream ;
typedef  TYPE_2__ IStream ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StreamVtbl ; 

__attribute__((used)) static IStream *create_test_stream(void)
{
    TestStream *stream;
    stream = HeapAlloc(GetProcessHeap(), 0, sizeof(*stream));
    stream->IStream_iface.lpVtbl = &StreamVtbl;
    stream->ref = 1;
    stream->pos = 0;
    return &stream->IStream_iface;
}