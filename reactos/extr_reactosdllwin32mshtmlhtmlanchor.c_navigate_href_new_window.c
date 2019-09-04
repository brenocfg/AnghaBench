#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {TYPE_1__* doc; } ;
struct TYPE_9__ {TYPE_2__ node; } ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
struct TYPE_6__ {TYPE_3__ basedoc; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_4__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_relative_uri (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  navigate_new_window (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT navigate_href_new_window(HTMLElement *element, nsAString *href_str, const WCHAR *target)
{
    const PRUnichar *href;
    IUri *uri;
    HRESULT hres;

    nsAString_GetData(href_str, &href);
    hres = create_relative_uri(element->node.doc->basedoc.window, href, &uri);
    if(FAILED(hres))
        return hres;

    hres = navigate_new_window(element->node.doc->basedoc.window, uri, target, NULL, NULL);
    IUri_Release(uri);
    return hres;
}