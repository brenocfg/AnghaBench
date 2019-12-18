#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sy; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SYMBOL ;

/* Variables and functions */
 int NUMKEYS ; 
 int /*<<< orphan*/  SUNDEFINED ; 
 TYPE_1__* TabKeys ; 
 int cmsstrcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SYMBOL BinSrchKey(const char *id)
{
    int l = 1;
    int r = NUMKEYS;
    int x, res;

    while (r >= l)
    {
        x = (l+r)/2;
        res = cmsstrcasecmp(id, TabKeys[x-1].id);
        if (res == 0) return TabKeys[x-1].sy;
        if (res < 0) r = x - 1;
        else l = x + 1;
    }

    return SUNDEFINED;
}