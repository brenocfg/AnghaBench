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
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
struct TYPE_5__ {int /*<<< orphan*/  cbSize; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ STATSTG ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Stat (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int /*<<< orphan*/  STREAM_SEEK_END ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT get_stream_size(IStream *stream, ULARGE_INTEGER *size)
{
    STATSTG statstg = {NULL};
    LARGE_INTEGER zero;
    HRESULT hres;

    hres = IStream_Stat(stream, &statstg, STATFLAG_NONAME);
    if(SUCCEEDED(hres)) {
        *size = statstg.cbSize;
        return S_OK;
    }

    zero.QuadPart = 0;
    return IStream_Seek(stream, zero, STREAM_SEEK_END, size);
}