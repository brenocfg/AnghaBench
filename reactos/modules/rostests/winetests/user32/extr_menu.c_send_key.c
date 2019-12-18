#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  wVk; } ;
struct TYPE_5__ {TYPE_2__ ki; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ TEST_INPUT ;
typedef  int /*<<< orphan*/  INPUT ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_KEYBOARD ; 
 int /*<<< orphan*/  KEYEVENTF_KEYUP ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pSendInput (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void send_key(WORD wVk)
{
    TEST_INPUT i[2];
    memset(i, 0, sizeof(i));
    i[0].type = i[1].type = INPUT_KEYBOARD;
    i[0].u.ki.wVk = i[1].u.ki.wVk = wVk;
    i[1].u.ki.dwFlags = KEYEVENTF_KEYUP;
    pSendInput(2, (INPUT *) i, sizeof(INPUT));
}