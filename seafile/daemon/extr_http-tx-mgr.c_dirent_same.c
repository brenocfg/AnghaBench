#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_4__ {scalar_t__ mode; scalar_t__ mtime; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafDirent ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
dirent_same (SeafDirent *dent1, SeafDirent *dent2)
{
    return (strcmp(dent1->id, dent2->id) == 0 &&
            dent1->mode == dent2->mode &&
            dent1->mtime == dent2->mtime);
}