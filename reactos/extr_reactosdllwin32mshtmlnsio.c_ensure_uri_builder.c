#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  uri_builder; int /*<<< orphan*/  uri; int /*<<< orphan*/  is_mutable; } ;
typedef  TYPE_1__ nsWineURI ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateIUriBuilder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  ensure_uri (TYPE_1__*) ; 
 int /*<<< orphan*/  invalidate_uri (TYPE_1__*) ; 

__attribute__((used)) static BOOL ensure_uri_builder(nsWineURI *This)
{
    if(!This->is_mutable) {
        WARN("Not mutable URI\n");
        return FALSE;
    }

    if(!This->uri_builder) {
        HRESULT hres;

        if(!ensure_uri(This))
            return FALSE;

        hres = CreateIUriBuilder(This->uri, 0, 0, &This->uri_builder);
        if(FAILED(hres)) {
            WARN("CreateIUriBuilder failed: %08x\n", hres);
            return FALSE;
        }
    }

    invalidate_uri(This);
    return TRUE;
}