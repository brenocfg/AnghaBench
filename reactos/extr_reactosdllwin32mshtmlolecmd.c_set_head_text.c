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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIPrintSettings ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  nsIPrintSettings_SetFooterStrCenter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetFooterStrLeft (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetFooterStrRight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetHeaderStrCenter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetHeaderStrLeft (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetHeaderStrRight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nsresult set_head_text(nsIPrintSettings *settings, LPCWSTR template, BOOL head, int pos)
{
    if(head) {
        switch(pos) {
        case 0:
            return nsIPrintSettings_SetHeaderStrLeft(settings, template);
        case 1:
            return nsIPrintSettings_SetHeaderStrRight(settings, template);
        case 2:
            return nsIPrintSettings_SetHeaderStrCenter(settings, template);
        }
    }else {
        switch(pos) {
        case 0:
            return nsIPrintSettings_SetFooterStrLeft(settings, template);
        case 1:
            return nsIPrintSettings_SetFooterStrRight(settings, template);
        case 2:
            return nsIPrintSettings_SetFooterStrCenter(settings, template);
        }
    }

    return NS_OK;
}