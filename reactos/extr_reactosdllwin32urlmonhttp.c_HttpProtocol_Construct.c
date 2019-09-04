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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  create_http_protocol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

HRESULT HttpProtocol_Construct(IUnknown *outer, void **ppv)
{
    TRACE("(%p %p)\n", outer, ppv);

    return create_http_protocol(FALSE, outer, ppv);
}