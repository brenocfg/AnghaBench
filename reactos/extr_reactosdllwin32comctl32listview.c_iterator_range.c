#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ upper; scalar_t__ lower; } ;
struct TYPE_8__ {TYPE_1__* ranges; TYPE_2__ range; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdpa; } ;
typedef  TYPE_2__ RANGE ;
typedef  TYPE_3__ ITERATOR ;

/* Variables and functions */
 scalar_t__ DPA_GetPtr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DPA_GetPtrCount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RANGE iterator_range(const ITERATOR *i)
{
    RANGE range;

    if (!i->ranges) return i->range;

    if (DPA_GetPtrCount(i->ranges->hdpa) > 0)
    {
        range.lower = (*(RANGE*)DPA_GetPtr(i->ranges->hdpa, 0)).lower;
        range.upper = (*(RANGE*)DPA_GetPtr(i->ranges->hdpa, DPA_GetPtrCount(i->ranges->hdpa) - 1)).upper;
    }
    else range.lower = range.upper = 0;

    return range;
}