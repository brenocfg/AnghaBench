#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * data; scalar_t__ is_mapped_file; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_1__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assembly_release (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_headers (TYPE_1__*) ; 

HRESULT assembly_from_hmodule(ASSEMBLY **out, HMODULE hmodule)
{
    ASSEMBLY *assembly;
    HRESULT hr;

    *out = NULL;

    assembly = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ASSEMBLY));
    if (!assembly)
        return E_OUTOFMEMORY;

    assembly->is_mapped_file = 0;

    assembly->data = (BYTE*)hmodule;

    hr = parse_headers(assembly);
    if (SUCCEEDED(hr))
        *out = assembly;
    else
        assembly_release(assembly);

    return hr;
}