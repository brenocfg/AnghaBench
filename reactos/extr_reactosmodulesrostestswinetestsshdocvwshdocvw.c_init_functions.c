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
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  hshdocvw ; 
 void* pParseURLFromOutsideSourceA ; 
 void* pParseURLFromOutsideSourceW ; 
 void* pURLSubRegQueryA ; 

__attribute__((used)) static void init_functions(void)
{
    hshdocvw = LoadLibraryA("shdocvw.dll");
    pURLSubRegQueryA = (void *) GetProcAddress(hshdocvw, (LPSTR) 151);
    pParseURLFromOutsideSourceA = (void *) GetProcAddress(hshdocvw, (LPSTR) 169);
    pParseURLFromOutsideSourceW = (void *) GetProcAddress(hshdocvw, (LPSTR) 170);
}