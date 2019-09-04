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
typedef  enum wined3d_pci_vendor { ____Placeholder_wined3d_pci_vendor } wined3d_pci_vendor ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int HW_VENDOR_AMD ; 
 int HW_VENDOR_INTEL ; 
 int HW_VENDOR_NVIDIA ; 
 int HW_VENDOR_SOFTWARE ; 
 int HW_VENDOR_VMWARE ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static enum wined3d_pci_vendor wined3d_guess_card_vendor(const char *gl_vendor_string, const char *gl_renderer)
{
    if (strstr(gl_vendor_string, "NVIDIA")
            || strstr(gl_vendor_string, "Nouveau")
            || strstr(gl_vendor_string, "nouveau"))
        return HW_VENDOR_NVIDIA;

    if (strstr(gl_vendor_string, "ATI")
            || strstr(gl_vendor_string, "Advanced Micro Devices, Inc.")
            || strstr(gl_vendor_string, "X.Org R300 Project")
            || strstr(gl_renderer, "AMD")
            || strstr(gl_renderer, "FirePro")
            || strstr(gl_renderer, "Radeon")
            || strstr(gl_renderer, "R100")
            || strstr(gl_renderer, "R200")
            || strstr(gl_renderer, "R300")
            || strstr(gl_renderer, "R600")
            || strstr(gl_renderer, "R700"))
        return HW_VENDOR_AMD;

    if (strstr(gl_vendor_string, "Intel(R)")
            /* Intel switched from Intel(R) to Intel® recently, so just match Intel. */
            || strstr(gl_renderer, "Intel")
            || strstr(gl_renderer, "i915")
            || strstr(gl_vendor_string, "Intel Inc."))
        return HW_VENDOR_INTEL;

    if (strstr(gl_renderer, "SVGA3D"))
        return HW_VENDOR_VMWARE;

    if (strstr(gl_vendor_string, "Mesa")
            || strstr(gl_vendor_string, "Brian Paul")
            || strstr(gl_vendor_string, "Tungsten Graphics, Inc")
            || strstr(gl_vendor_string, "VMware, Inc."))
        return HW_VENDOR_SOFTWARE;

    FIXME("Received unrecognized GL_VENDOR %s. Returning HW_VENDOR_NVIDIA.\n", debugstr_a(gl_vendor_string));

    return HW_VENDOR_NVIDIA;
}