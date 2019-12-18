#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINTN ;
typedef  int UINT64 ;
struct TYPE_6__ {TYPE_2__* ConOut; } ;
struct TYPE_5__ {TYPE_1__* Mode; int /*<<< orphan*/  QueryMode; } ;
struct TYPE_4__ {int /*<<< orphan*/  Mode; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* ST ; 
 int SYSTEM_FONT_HEIGHT ; 
 int SYSTEM_FONT_WIDTH ; 
 int /*<<< orphan*/  uefi_call_wrapper (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static UINT64 text_area_from_font_size(void) {
        EFI_STATUS err;
        UINT64 text_area;
        UINTN rows, columns;

        err = uefi_call_wrapper(ST->ConOut->QueryMode, 4, ST->ConOut, ST->ConOut->Mode->Mode, &columns, &rows);
        if (EFI_ERROR(err)) {
                columns = 80;
                rows = 25;
        }

        text_area = SYSTEM_FONT_WIDTH * SYSTEM_FONT_HEIGHT * (UINT64)rows * (UINT64)columns;

        return text_area;
}