#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dname; } ;
typedef  TYPE_1__ IndexDirent ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) inline static gboolean
is_duplicate_dirent (GList *dirents, const char *dname)
{
    if (!dirents)
        return FALSE;

    IndexDirent *dent = dirents->data;

    return (strcmp(dent->dname, dname) == 0);
}