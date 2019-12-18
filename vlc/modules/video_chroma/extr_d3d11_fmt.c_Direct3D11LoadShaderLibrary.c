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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HINSTANCE Direct3D11LoadShaderLibrary(void)
{
    HINSTANCE instance = NULL;
    /* d3dcompiler_47 is the latest on windows 8.1 */
    for (int i = 47; i > 41; --i) {
        WCHAR filename[19];
        _snwprintf(filename, 19, TEXT("D3DCOMPILER_%d.dll"), i);
        instance = LoadLibrary(filename);
        if (instance) break;
    }
    return instance;
}