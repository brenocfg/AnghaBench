#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tab ;
struct TYPE_3__ {int member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dvb_int_map_t ;

/* Variables and functions */
#define  HIERARCHY_1 132 
#define  HIERARCHY_2 131 
#define  HIERARCHY_4 130 
#define  HIERARCHY_AUTO 129 
#define  HIERARCHY_NONE 128 
 int dvb_parse_int (int,TYPE_1__ const*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int dvb_parse_hierarchy (int i)
{
    static const dvb_int_map_t tab[] = {
        { HIERARCHY_AUTO, -1 },
        { HIERARCHY_NONE,  0 },
        { HIERARCHY_1,     1 },
        { HIERARCHY_2,     2 },
        { HIERARCHY_4,     4 },
    };
    return dvb_parse_int (i, tab, sizeof (tab) / sizeof (*tab),
                          HIERARCHY_AUTO);
}