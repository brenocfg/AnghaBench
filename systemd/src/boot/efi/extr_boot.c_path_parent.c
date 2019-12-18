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
typedef  int UINTN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 scalar_t__ AllocatePool (int) ; 
 int /*<<< orphan*/  CopyMem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EndDevicePath ; 
 scalar_t__ NextDevicePathNode (int /*<<< orphan*/ *) ; 

EFI_DEVICE_PATH *path_parent(EFI_DEVICE_PATH *path, EFI_DEVICE_PATH *node) {
        EFI_DEVICE_PATH *parent;
        UINTN len;

        len = (UINT8*) NextDevicePathNode(node) - (UINT8*) path;
        parent = (EFI_DEVICE_PATH*) AllocatePool(len + sizeof(EFI_DEVICE_PATH));
        CopyMem(parent, path, len);
        CopyMem((UINT8*) parent + len, EndDevicePath, sizeof(EFI_DEVICE_PATH));

        return parent;
}