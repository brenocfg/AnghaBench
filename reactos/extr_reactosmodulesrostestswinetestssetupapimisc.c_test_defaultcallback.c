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
struct default_callback_context {struct default_callback_context* message; int /*<<< orphan*/ * progress; int /*<<< orphan*/ * owner; struct default_callback_context* magic; } ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  struct default_callback_context* DWORD ;

/* Variables and functions */
 struct default_callback_context* SetupInitDefaultQueueCallback (int /*<<< orphan*/ *) ; 
 struct default_callback_context* SetupInitDefaultQueueCallbackEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct default_callback_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupTermDefaultQueueCallback (struct default_callback_context*) ; 
 struct default_callback_context* WM_USER ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,struct default_callback_context*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_defaultcallback(void)
{
    struct default_callback_context *ctxt;
    static const DWORD magic = 0x43515053; /* "SPQC" */
    HWND owner, progress;

    owner = (HWND)0x123;
    progress = (HWND)0x456;
    ctxt = SetupInitDefaultQueueCallbackEx(owner, progress, WM_USER, 0, NULL);
    ok(ctxt != NULL, "got %p\n", ctxt);

    ok(ctxt->magic == magic || broken(ctxt->magic != magic) /* win2000 */, "got magic 0x%08x\n", ctxt->magic);
    if (ctxt->magic == magic)
    {
        ok(ctxt->owner == owner, "got %p, expected %p\n", ctxt->owner, owner);
        ok(ctxt->progress == progress, "got %p, expected %p\n", ctxt->progress, progress);
        ok(ctxt->message == WM_USER, "got %d, expected %d\n", ctxt->message, WM_USER);
        SetupTermDefaultQueueCallback(ctxt);
    }
    else
    {
        win_skip("Skipping tests on old systems.\n");
        SetupTermDefaultQueueCallback(ctxt);
        return;
    }

    ctxt = SetupInitDefaultQueueCallback(owner);
    ok(ctxt->magic == magic, "got magic 0x%08x\n", ctxt->magic);
    ok(ctxt->owner == owner, "got %p, expected %p\n", ctxt->owner, owner);
    ok(ctxt->progress == NULL, "got %p, expected %p\n", ctxt->progress, progress);
    ok(ctxt->message == 0, "got %d\n", ctxt->message);
    SetupTermDefaultQueueCallback(ctxt);
}