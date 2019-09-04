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
struct MemWrittenTracker {scalar_t__ written; scalar_t__ cbData; scalar_t__ pbData; } ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,scalar_t__) ; 

__attribute__((used)) static BOOL CRYPT_MemOutputFunc(void *handle, const void *buffer, DWORD size)
{
    struct MemWrittenTracker *tracker = handle;
    BOOL ret;

    if (tracker->written + size > tracker->cbData)
    {
        SetLastError(ERROR_MORE_DATA);
        /* Update written so caller can notify its caller of the required size
         */
        tracker->written += size;
        ret = FALSE;
    }
    else
    {
        memcpy(tracker->pbData + tracker->written, buffer, size);
        tracker->written += size;
        ret = TRUE;
    }
    return ret;
}