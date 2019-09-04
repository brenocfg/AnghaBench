#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_CUR ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline HRESULT advance_stream(IStream *stream, ULONG bytes)
{
    LARGE_INTEGER move;
    HRESULT ret;

    move.QuadPart = bytes;

    ret = IStream_Seek(stream, move, STREAM_SEEK_CUR, NULL);
    if (FAILED(ret))
        WARN("IStream_Seek failed: %08x\n", ret);

    return ret;
}