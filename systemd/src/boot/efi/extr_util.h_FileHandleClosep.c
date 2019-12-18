#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Close; } ;
typedef  TYPE_1__* EFI_FILE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  uefi_call_wrapper (int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static inline void FileHandleClosep(EFI_FILE_HANDLE *handle) {
        if (!*handle)
                return;

        uefi_call_wrapper((*handle)->Close, 1, *handle);
}