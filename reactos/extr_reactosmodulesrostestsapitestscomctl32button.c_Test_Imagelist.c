#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ himl; scalar_t__ uAlign; int /*<<< orphan*/  margin; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HIMAGELIST ;
typedef  TYPE_1__ BUTTON_IMAGELIST ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GETIMAGELIST ; 
 int /*<<< orphan*/  BCM_SETIMAGELIST ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void Test_Imagelist()
{
    HWND hwnd1;
    BOOL ret;
    BUTTON_IMAGELIST imlData;

    hwnd1 = CreateWindowW(L"Button", L"Test2", 0, 10, 10, 100, 100, 0, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");

    ret = SendMessageW(hwnd1, BCM_GETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_GETIMAGELIST to succeed\n");
    ok (imlData.himl == 0, "Expected 0 himl\n");
    ok (imlData.uAlign == 0, "Expected 0 uAlign\n");
    ok_rect(imlData.margin, 0, 0, 0, 0);
    
    SetRect(&imlData.margin, 0,0,0,1);
    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == FALSE, "Expected BCM_SETIMAGELIST to fail\n"); /* This works in win10 */

    imlData.himl = (HIMAGELIST)0xdead;
    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_SETIMAGELIST to fail\n");
    
    ret = SendMessageW(hwnd1, BCM_GETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_GETIMAGELIST to succeed\n");
    ok (imlData.himl == (HIMAGELIST)0xdead, "Expected 0 himl\n");
    ok (imlData.uAlign == 0, "Expected 0 uAlign\n");
    ok_rect(imlData.margin, 0, 0, 0, 1);

    imlData.himl = 0;
    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == FALSE, "Expected BCM_SETIMAGELIST to fail\n"); /* This works in win10 */

    DestroyWindow(hwnd1);
}