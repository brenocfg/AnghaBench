#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {TYPE_1__* nsevent_listener; } ;
struct TYPE_5__ {int /*<<< orphan*/  htmlevent_listener; } ;
typedef  TYPE_2__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  detach_nslistener (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void detach_nsevent(HTMLDocumentNode *doc, const WCHAR *type)
{
    detach_nslistener(doc, type, &doc->nsevent_listener->htmlevent_listener, TRUE);
}