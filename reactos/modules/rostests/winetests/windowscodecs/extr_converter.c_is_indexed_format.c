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
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_WICPixelFormat1bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat2bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat4bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat8bppIndexed ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL is_indexed_format(const GUID *format)
{
    if (IsEqualGUID(format, &GUID_WICPixelFormat1bppIndexed) ||
        IsEqualGUID(format, &GUID_WICPixelFormat2bppIndexed) ||
        IsEqualGUID(format, &GUID_WICPixelFormat4bppIndexed) ||
        IsEqualGUID(format, &GUID_WICPixelFormat8bppIndexed))
        return TRUE;

    return FALSE;
}