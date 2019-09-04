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
typedef  int /*<<< orphan*/  PHANDLE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static NTSTATUS
OpenCurrentConfigKey (PHANDLE KeyHandle)
{
    OBJECT_ATTRIBUTES Attributes;
    UNICODE_STRING KeyName =
        RTL_CONSTANT_STRING(L"\\Registry\\Machine\\System\\CurrentControlSet\\Hardware Profiles\\Current");

    TRACE("OpenCurrentConfigKey()\n");

    InitializeObjectAttributes(&Attributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    return NtOpenKey(KeyHandle,
                     MAXIMUM_ALLOWED,
                     &Attributes);
}