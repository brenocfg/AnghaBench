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
struct TYPE_3__ {scalar_t__ lpbiOut; scalar_t__ lpbiIn; int /*<<< orphan*/  querymsg; int /*<<< orphan*/  wMode; int /*<<< orphan*/  fccHandler; int /*<<< orphan*/  fccType; } ;
typedef  TYPE_1__ driver_info_t ;
typedef  int /*<<< orphan*/  HIC ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  ICClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICSendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HIC try_driver(driver_info_t *info)
{
    HIC   hic;

    if ((hic = ICOpen(info->fccType, info->fccHandler, info->wMode))) 
    {
	if (!ICSendMessage(hic, info->querymsg, (DWORD_PTR)info->lpbiIn, (DWORD_PTR)info->lpbiOut))
	    return hic;
	ICClose(hic);
    }
    return 0;
}