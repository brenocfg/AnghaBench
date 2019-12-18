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

/* Variables and functions */

__attribute__((used)) static const char* get_simple_type(char c)
{
    const char* type_string;
    
    switch (c)
    {
    case 'C': type_string = "signed char"; break;
    case 'D': type_string = "char"; break;
    case 'E': type_string = "unsigned char"; break;
    case 'F': type_string = "short"; break;
    case 'G': type_string = "unsigned short"; break;
    case 'H': type_string = "int"; break;
    case 'I': type_string = "unsigned int"; break;
    case 'J': type_string = "long"; break;
    case 'K': type_string = "unsigned long"; break;
    case 'M': type_string = "float"; break;
    case 'N': type_string = "double"; break;
    case 'O': type_string = "long double"; break;
    case 'X': type_string = "void"; break;
    case 'Z': type_string = "..."; break;
    default:  type_string = NULL; break;
    }
    return type_string;
}