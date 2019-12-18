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
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  CHAR8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmpa (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

EFI_STATUS parse_boolean(const CHAR8 *v, BOOLEAN *b) {
        if (!v)
                return EFI_INVALID_PARAMETER;

        if (strcmpa(v, (CHAR8 *)"1") == 0 ||
            strcmpa(v, (CHAR8 *)"yes") == 0 ||
            strcmpa(v, (CHAR8 *)"y") == 0 ||
            strcmpa(v, (CHAR8 *)"true") == 0) {
                *b = TRUE;
                return EFI_SUCCESS;
        }

        if (strcmpa(v, (CHAR8 *)"0") == 0 ||
            strcmpa(v, (CHAR8 *)"no") == 0 ||
            strcmpa(v, (CHAR8 *)"n") == 0 ||
            strcmpa(v, (CHAR8 *)"false") == 0) {
                *b = FALSE;
                return EFI_SUCCESS;
        }

        return EFI_INVALID_PARAMETER;
}