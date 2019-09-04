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
typedef  int /*<<< orphan*/  length ;
typedef  int /*<<< orphan*/  clipformat ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,int*,int,int*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int read_clipformat(IStream *stream)
{
    HRESULT hr;
    ULONG bytes;
    int length, clipformat = -2;

    hr = IStream_Read(stream, &length, sizeof(length), &bytes);
    if (hr != S_OK || bytes != sizeof(length))
        return -2;
    if (length == 0)
        return 0;
    if (length == -1)
    {
        hr = IStream_Read(stream, &clipformat, sizeof(clipformat), &bytes);
        if (hr != S_OK || bytes != sizeof(clipformat))
            return -2;
    }
    else
        ok(0, "unhandled clipformat length %d\n", length);

    return clipformat;
}