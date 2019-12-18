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
struct message {int flags; scalar_t__ stage; int /*<<< orphan*/  id; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  WM_TD_CALLBACK ; 
 int id ; 
 int lparam ; 
 int sent ; 
 int wparam ; 

__attribute__((used)) static void init_test_message(UINT message, WPARAM wParam, LPARAM lParam, struct message *msg)
{
    msg->message = WM_TD_CALLBACK;
    msg->flags = sent|wparam|lparam|id;
    msg->wParam = wParam;
    msg->lParam = lParam;
    msg->id = message;
    msg->stage = 0;
}