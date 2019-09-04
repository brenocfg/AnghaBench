#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  web_browser; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ HHInfo ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AppendFullPathURL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  navigate_url (TYPE_1__*,int /*<<< orphan*/ *) ; 

BOOL NavigateToChm(HHInfo *info, LPCWSTR file, LPCWSTR index)
{
    WCHAR buf[INTERNET_MAX_URL_LENGTH];

    TRACE("%p %s %s\n", info, debugstr_w(file), debugstr_w(index));

    if ((!info->web_browser) || !AppendFullPathURL(file, buf, index))
        return FALSE;

    return SUCCEEDED(navigate_url(info, buf));
}