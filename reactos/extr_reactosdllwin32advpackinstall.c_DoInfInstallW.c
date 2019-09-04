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
struct TYPE_4__ {int /*<<< orphan*/  dir; int /*<<< orphan*/  section_name; int /*<<< orphan*/  inf_name; } ;
typedef  TYPE_1__ SETUPCOMMAND_PARAMSW ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  ADVInfo ;

/* Variables and functions */
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 scalar_t__ adv_install (int /*<<< orphan*/ *) ; 
 scalar_t__ install_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  install_release (int /*<<< orphan*/ *) ; 
 scalar_t__ spapi_install (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT DoInfInstallW(const SETUPCOMMAND_PARAMSW *setup)
{
    ADVInfo info;
    HRESULT hr;

    TRACE("(%p)\n", setup);

    ZeroMemory(&info, sizeof(ADVInfo));

    hr = install_init(setup->inf_name, setup->section_name, setup->dir, 0, &info);
    if (hr != S_OK)
        goto done;

    hr = spapi_install(&info);
    if (hr != S_OK)
        goto done;

    hr = adv_install(&info);

done:
    install_release(&info);

    return S_OK;
}