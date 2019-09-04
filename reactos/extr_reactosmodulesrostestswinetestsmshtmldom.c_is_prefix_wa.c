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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int FALSE ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (scalar_t__*,char const*) ; 
 int lstrlenA (char const*) ; 

__attribute__((used)) static BOOL is_prefix_wa(const WCHAR *strw, const char *prefix)
{
    int len, prefix_len;
    CHAR buf[512];

    len = WideCharToMultiByte(CP_ACP, 0, strw, -1, buf, sizeof(buf), NULL, NULL)-1;
    prefix_len = lstrlenA(prefix);
    if(len < prefix_len)
        return FALSE;

    buf[prefix_len] = 0;
    return !lstrcmpA(buf, prefix);
}