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
typedef  enum module_type { ____Placeholder_module_type } module_type ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  DMT_ELF 130 
#define  DMT_MACHO 129 
#define  DMT_PE 128 

__attribute__((used)) static const char*      get_module_type(enum module_type type, BOOL virtual)
{
    switch (type)
    {
    case DMT_ELF: return virtual ? "Virtual ELF" : "ELF";
    case DMT_PE: return virtual ? "Virtual PE" : "PE";
    case DMT_MACHO: return virtual ? "Virtual Mach-O" : "Mach-O";
    default: return "---";
    }
}