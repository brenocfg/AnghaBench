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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  ASSEMBLY ;

/* Variables and functions */
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_clr_metadata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_pe_header (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT parse_headers(ASSEMBLY *assembly)
{
    HRESULT hr;

    hr = parse_pe_header(assembly);

    if (SUCCEEDED(hr))
        hr = parse_clr_metadata(assembly);

    return hr;
}