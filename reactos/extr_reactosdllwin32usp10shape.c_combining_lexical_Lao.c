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
typedef  int WCHAR ;

/* Variables and functions */

__attribute__((used)) static int combining_lexical_Lao(WCHAR c)
{
    enum {Lao_Norm=0, Lao_ABOVE1, Lao_ABOVE2, Lao_BELOW1, Lao_BELOW2, Lao_AM};

   switch(c)
    {
        case 0xEB1:
        case 0xEB4:
        case 0xEB5:
        case 0xEB6:
        case 0xEB7:
        case 0xEBB:
        case 0xECD: return Lao_ABOVE1;
        case 0xEC8:
        case 0xEC9:
        case 0xECA:
        case 0xECB:
        case 0xECC: return Lao_ABOVE2;
        case 0xEBC: return Lao_BELOW1;
        case 0xEB8:
        case 0xEB9: return Lao_BELOW2;
        case 0xEB3: return Lao_AM;
        default: return Lao_Norm;
    }
}