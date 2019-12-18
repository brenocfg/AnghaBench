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
struct wndclass_redirect_data {int name_offset; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int cbSize; scalar_t__ lpData; } ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ACTCTX_SECTION_KEYED_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION ; 
 int /*<<< orphan*/  FindActCtxSectionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR* get_versioned_classname(const WCHAR *name)
{
    struct wndclass_redirect_data *wnddata;
    ACTCTX_SECTION_KEYED_DATA data;
    BOOL ret;

    memset(&data, 0, sizeof(data));
    data.cbSize = sizeof(data);
    ret = FindActCtxSectionStringW(0, NULL, ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, name, &data);
    ok(ret, "Failed to find class redirection section, error %u\n", GetLastError());
    wnddata = (struct wndclass_redirect_data*)data.lpData;
    return (WCHAR*)((BYTE*)wnddata + wnddata->name_offset);
}