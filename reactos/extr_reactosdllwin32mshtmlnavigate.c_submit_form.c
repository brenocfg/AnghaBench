#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ request_data_t ;
typedef  int /*<<< orphan*/  nsIInputStream ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  readystate_locked; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_2__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int BINDING_NAVIGATED ; 
 int BINDING_SUBMIT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  navigate_new_window (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  navigate_uri (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  read_post_data_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  release_request_data (TYPE_1__*) ; 
 int /*<<< orphan*/  translate_uri (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT submit_form(HTMLOuterWindow *window, const WCHAR *target, IUri *submit_uri, nsIInputStream *post_stream)
{
    request_data_t request_data = {NULL};
    HRESULT hres;

    hres = read_post_data_stream(post_stream, TRUE, NULL, &request_data);
    if(FAILED(hres))
        return hres;

    if(window) {
        IUri *uri;
        BSTR display_uri;

        window->readystate_locked++;

        hres = translate_uri(window, submit_uri, &display_uri, &uri);
        if(SUCCEEDED(hres)) {
            hres = navigate_uri(window, uri, display_uri, &request_data, BINDING_NAVIGATED|BINDING_SUBMIT);
            IUri_Release(uri);
            SysFreeString(display_uri);
        }

        window->readystate_locked--;
    }else
        hres = navigate_new_window(window, submit_uri, target, &request_data, NULL);

    release_request_data(&request_data);
    return hres;
}