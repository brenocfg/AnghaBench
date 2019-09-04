#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_4__ {TYPE_1__* Peb; } ;
struct TYPE_3__ {int SessionId; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateMutexA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  DIRECTORY_QUERY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* NtCurrentTeb () ; 
 int /*<<< orphan*/  OBJ_OPENIF ; 
 scalar_t__ is_correct_dir (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtClose (scalar_t__) ; 
 scalar_t__ pNtOpenDirectoryObject (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static HANDLE get_base_dir(void)
{
    static const char objname[] = "om.c_get_base_dir_obj";
    NTSTATUS status;
    UNICODE_STRING str;
    OBJECT_ATTRIBUTES attr;
    HANDLE dir, h;
    char name[40];

    h = CreateMutexA(NULL, FALSE, objname);
    ok(h != 0, "CreateMutexA failed got ret=%p (%d)\n", h, GetLastError());
    InitializeObjectAttributes(&attr, &str, OBJ_OPENIF, 0, NULL);

    sprintf( name, "\\BaseNamedObjects\\Session\\%u", NtCurrentTeb()->Peb->SessionId );
    pRtlCreateUnicodeStringFromAsciiz(&str, name );
    status = pNtOpenDirectoryObject(&dir, DIRECTORY_QUERY, &attr);
    pRtlFreeUnicodeString(&str);
    if (!status && is_correct_dir( dir, objname )) goto done;
    if (!status) pNtClose( dir );

    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects");
    status = pNtOpenDirectoryObject(&dir, DIRECTORY_QUERY, &attr);
    pRtlFreeUnicodeString(&str);
    if (!status && is_correct_dir( dir, objname )) goto done;
    if (!status) pNtClose( dir );

    dir = 0;

done:
    pNtClose( h );
    return dir;
}