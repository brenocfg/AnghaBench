#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_9__ {int /*<<< orphan*/  is_doc_uri; } ;
typedef  TYPE_2__ nsWineURI ;
struct TYPE_10__ {TYPE_1__* doc_obj; } ;
struct TYPE_8__ {int /*<<< orphan*/  nscontainer; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_3__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_nsuri (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**) ; 

HRESULT create_doc_uri(HTMLOuterWindow *window, IUri *iuri, nsWineURI **ret)
{
    nsWineURI *uri;
    nsresult nsres;

    nsres = create_nsuri(iuri, window, window->doc_obj->nscontainer, NULL, &uri);
    if(NS_FAILED(nsres))
        return E_FAIL;

    uri->is_doc_uri = TRUE;

    *ret = uri;
    return S_OK;
}