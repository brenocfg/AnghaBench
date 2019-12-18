#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int member_0; int /*<<< orphan*/ * lpSource; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ ACTCTXW ;
typedef  int /*<<< orphan*/  ACTCTX ;

/* Variables and functions */
 int /*<<< orphan*/  CreateActCtxW (TYPE_1__*) ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/ *,int) ; 

HANDLE _CreateActCtxFromFile(LPCWSTR FileName)
{
    ACTCTXW ActCtx = {sizeof(ACTCTX)};
    WCHAR buffer[MAX_PATH] , *separator;

    ok (GetModuleFileNameW(NULL, buffer, MAX_PATH), "GetModuleFileName failed\n");
    separator = wcsrchr(buffer, L'\\');
    if (separator)
        wcscpy(separator + 1, FileName);

    ActCtx.lpSource = buffer;

    return CreateActCtxW(&ActCtx);
}