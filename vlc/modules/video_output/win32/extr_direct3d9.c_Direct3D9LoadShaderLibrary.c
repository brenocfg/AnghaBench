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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HINSTANCE Direct3D9LoadShaderLibrary(void)
{
    HINSTANCE instance = NULL;
    for (int i = 43; i > 23; --i) {
        WCHAR filename[16];
        _snwprintf(filename, ARRAY_SIZE(filename), TEXT("D3dx9_%d.dll"), i);
        instance = LoadLibrary(filename);
        if (instance)
            break;
    }
    return instance;
}