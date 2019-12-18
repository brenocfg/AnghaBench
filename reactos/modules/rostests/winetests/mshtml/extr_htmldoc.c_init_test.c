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
typedef  enum load_state_t { ____Placeholder_load_state_t } load_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CallUIActivate_None ; 
 int /*<<< orphan*/  DocHostUIHandler ; 
 void* FALSE ; 
 int /*<<< orphan*/  call_UIActivate ; 
 void* complete ; 
 int /*<<< orphan*/  doc_hwnd ; 
 int /*<<< orphan*/ * doc_unk ; 
 void* editmode ; 
 int /*<<< orphan*/ * expect_uihandler_iface ; 
 void* inplace_deactivated ; 
 void* ipsex ; 
 int /*<<< orphan*/ * last_hwnd ; 
 void* load_from_stream ; 
 int load_state ; 
 int /*<<< orphan*/ * nav_url ; 
 scalar_t__ protocol_read ; 
 void* set_clientsite ; 
 scalar_t__ stream_read ; 
 void* testing_submit ; 

__attribute__((used)) static void init_test(enum load_state_t ls) {
    doc_unk = NULL;
    doc_hwnd = last_hwnd = NULL;
    set_clientsite = FALSE;
    load_from_stream = FALSE;
    call_UIActivate = CallUIActivate_None;
    load_state = ls;
    editmode = FALSE;
    stream_read = 0;
    protocol_read = 0;
    nav_url = NULL;
    ipsex = FALSE;
    inplace_deactivated = FALSE;
    complete = FALSE;
    testing_submit = FALSE;
    expect_uihandler_iface = &DocHostUIHandler;
}