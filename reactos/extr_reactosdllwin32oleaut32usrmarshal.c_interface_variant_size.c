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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  LOWORD (int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int WdtpInterfacePointer_UserSize (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned interface_variant_size(ULONG *pFlags, REFIID riid, IUnknown *punk)
{
    ULONG size = 0;

    if (punk)
    {
        size = WdtpInterfacePointer_UserSize(pFlags, LOWORD(*pFlags), 0, punk, riid);
        if (!size)
        {
            ERR("interface variant buffer size calculation failed\n");
            return 0;
        }
    }
    size += sizeof(ULONG);
    TRACE("wire-size extra of interface variant is %d\n", size);
    return size;
}