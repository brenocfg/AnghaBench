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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  VideoRenderer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT VideoRendererDefault_create(IUnknown * pUnkOuter, LPVOID * ppv)
{
    /* TODO: Attempt to use the VMR-7 renderer instead when possible */
    return VideoRenderer_create(pUnkOuter, ppv);
}