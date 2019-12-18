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
typedef  int /*<<< orphan*/  CHAR16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int StrLen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  efivar_set_raw (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loader_guid ; 

EFI_STATUS efivar_set(const CHAR16 *name, const CHAR16 *value, BOOLEAN persistent) {
        return efivar_set_raw(&loader_guid, name, value, value ? (StrLen(value)+1) * sizeof(CHAR16) : 0, persistent);
}