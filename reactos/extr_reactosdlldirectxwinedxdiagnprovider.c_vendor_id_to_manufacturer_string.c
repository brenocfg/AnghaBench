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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static const WCHAR *vendor_id_to_manufacturer_string(DWORD vendor_id)
{
    static const WCHAR atiW[] = {'A','T','I',' ','T','e','c','h','n','o','l','o','g','i','e','s',' ','I','n','c','.',0};
    static const WCHAR nvidiaW[] = {'N','V','I','D','I','A',0};
    static const WCHAR intelW[] = {'I','n','t','e','l',' ','C','o','r','p','o','r','a','t','i','o','n',0};
    static const WCHAR unknownW[] = {'U','n','k','n','o','w','n',0};

    /* Enumeration copied from dlls/wined3d/wined3d_private.h and slightly modified. */
    enum pci_vendor
    {
        HW_VENDOR_AMD = 0x1002,
        HW_VENDOR_NVIDIA = 0x10de,
        HW_VENDOR_INTEL = 0x8086,
    };

    switch (vendor_id)
    {
    case HW_VENDOR_AMD:
        return atiW;
    case HW_VENDOR_NVIDIA:
        return nvidiaW;
    case HW_VENDOR_INTEL:
        return intelW;
    default:
        FIXME("Unknown PCI vendor ID 0x%04x\n", vendor_id);
        return unknownW;
    }
}