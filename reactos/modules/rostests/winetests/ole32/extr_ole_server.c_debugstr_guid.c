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
struct TYPE_3__ {char const* name; int /*<<< orphan*/  guid; } ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* guid_name ; 
 char const* wine_dbgstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *debugstr_guid(const GUID *guid)
{
    int i;

    if (!guid) return "(null)";

    for (i = 0; i < ARRAY_SIZE(guid_name); i++)
    {
        if (IsEqualIID(guid, guid_name[i].guid))
            return guid_name[i].name;
    }

    return wine_dbgstr_guid(guid);
}