#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ Min; scalar_t__ Max; } ;
struct TYPE_10__ {TYPE_1__ Success; int /*<<< orphan*/  Path; scalar_t__ Expand; } ;
typedef  TYPE_2__ WCHAR ;
typedef  size_t ULONG ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ExpandEnvironmentStringsW (int /*<<< orphan*/ ,TYPE_2__*,size_t) ; 
 int MAX_PATH ; 
 int SfcIsFileProtected (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  StringCchCopyW (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 size_t _countof (TYPE_2__*) ; 
 scalar_t__ g_WinVersion ; 
 int /*<<< orphan*/  ok (int,char*,size_t,scalar_t__,TYPE_2__*) ; 
 TYPE_2__* tests ; 

__attribute__((used)) static void Test_ProtectedFiles()
{
    ULONG n;
    BOOL Protected;
    WCHAR Buffer[MAX_PATH * 3];

    for (n = 0; n < _countof(tests); ++n)
    {
        if (tests[n].Expand)
            ExpandEnvironmentStringsW(tests[n].Path, Buffer, _countof(Buffer));
        else
            StringCchCopyW(Buffer, _countof(Buffer), tests[n].Path);

        Protected = SfcIsFileProtected(NULL, Buffer);

        if (g_WinVersion >= tests[n].Success.Min && g_WinVersion <= tests[n].Success.Max)
        {
            ok(Protected, "[%lu,0x%04lx]: Failed: %S\n", n, g_WinVersion, Buffer);
        }
        else
        {
            ok(!Protected, "[%lu,0x%04lx]: Succeeded: %S\n", n, g_WinVersion, Buffer);
        }
    }
}