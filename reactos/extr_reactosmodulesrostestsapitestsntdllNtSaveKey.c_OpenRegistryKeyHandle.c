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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  PHANDLE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  ACCESS_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
OpenRegistryKeyHandle(PHANDLE KeyHandle,
                      ACCESS_MASK AccessMask,
                      PWCHAR RegistryPath)
{
    UNICODE_STRING KeyName;
    OBJECT_ATTRIBUTES Attributes;

    RtlInitUnicodeString(&KeyName, RegistryPath);
    InitializeObjectAttributes(&Attributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    return NtOpenKey(KeyHandle, AccessMask, &Attributes);
}