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
typedef  enum console_mode_change_type { ____Placeholder_console_mode_change_type } console_mode_change_type ;
typedef  scalar_t__ UINTN ;
struct TYPE_6__ {TYPE_2__* ConOut; } ;
struct TYPE_5__ {TYPE_1__* Mode; } ;
struct TYPE_4__ {scalar_t__ MaxMode; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int CONSOLE_MODE_AUTO ; 
 int CONSOLE_MODE_MAX ; 
 TYPE_3__* ST ; 
 int /*<<< orphan*/  change_mode (scalar_t__) ; 
 int /*<<< orphan*/  mode_auto (scalar_t__*) ; 

EFI_STATUS console_set_mode(UINTN *mode, enum console_mode_change_type how) {
        if (how == CONSOLE_MODE_AUTO)
                return mode_auto(mode);

        if (how == CONSOLE_MODE_MAX) {
                /* Note: MaxMode is the number of modes, not the last mode. */
                if (ST->ConOut->Mode->MaxMode > 0)
                        *mode = ST->ConOut->Mode->MaxMode-1;
                else
                        *mode = 0;
        }

        return change_mode(*mode);
}