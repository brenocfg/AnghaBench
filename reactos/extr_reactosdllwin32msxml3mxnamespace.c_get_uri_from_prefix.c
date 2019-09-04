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
struct nscontext {int count; TYPE_1__* ns; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/ * uri; int /*<<< orphan*/  prefix; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT get_uri_from_prefix(const struct nscontext *ctxt, const WCHAR *prefix, BSTR *uri)
{
    int i;

    for (i = 0; i < ctxt->count; i++)
        if (!strcmpW(ctxt->ns[i].prefix, prefix))
        {
            *uri = ctxt->ns[i].uri;
            return S_OK;
        }

    *uri = NULL;
    return S_FALSE;
}