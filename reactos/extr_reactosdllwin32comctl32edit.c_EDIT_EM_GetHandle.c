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
struct TYPE_4__ {int style; int /*<<< orphan*/  hlocapp; int /*<<< orphan*/  hloc32W; } ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_UnlockBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  LocalSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HLOCAL EDIT_EM_GetHandle(EDITSTATE *es)
{
    if (!(es->style & ES_MULTILINE))
        return 0;

    EDIT_UnlockBuffer(es, TRUE);

    /* The text buffer handle belongs to the app */
    es->hlocapp = es->hloc32W;

    TRACE("Returning %p, LocalSize() = %ld\n", es->hlocapp, LocalSize(es->hlocapp));
    return es->hlocapp;
}