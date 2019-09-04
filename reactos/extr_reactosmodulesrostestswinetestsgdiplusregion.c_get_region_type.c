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
typedef  int /*<<< orphan*/  GpRegion ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__* GdipAlloc (scalar_t__) ; 
 int /*<<< orphan*/  GdipFree (scalar_t__*) ; 
 scalar_t__ GdipGetRegionData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetRegionDataSize (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ InsufficientBuffer ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static DWORD get_region_type(GpRegion *region)
{
    DWORD *data;
    DWORD size;
    DWORD result;
    DWORD status;
    status = GdipGetRegionDataSize(region, &size);
    expect(Ok, status);
    data = GdipAlloc(size);
    status = GdipGetRegionData(region, (BYTE*)data, size, NULL);
    ok(status == Ok || status == InsufficientBuffer, "unexpected status 0x%x\n", status);
    result = data[4];
    GdipFree(data);
    return result;
}