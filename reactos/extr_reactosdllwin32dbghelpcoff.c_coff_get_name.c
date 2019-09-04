#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Long; scalar_t__ Short; } ;
struct TYPE_6__ {TYPE_1__ Name; int /*<<< orphan*/  ShortName; } ;
struct TYPE_7__ {TYPE_2__ N; } ;
typedef  TYPE_3__ IMAGE_SYMBOL ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char*	coff_get_name(const IMAGE_SYMBOL* coff_sym, 
                                      const char* coff_strtab)
{
    static	char	namebuff[9];
    const char*		nampnt;

    if (coff_sym->N.Name.Short)
    {
        memcpy(namebuff, coff_sym->N.ShortName, 8);
        namebuff[8] = '\0';
        nampnt = &namebuff[0];
    }
    else
    {
        nampnt = coff_strtab + coff_sym->N.Name.Long;
    }

    if (nampnt[0] == '_') nampnt++;
    return nampnt;
}