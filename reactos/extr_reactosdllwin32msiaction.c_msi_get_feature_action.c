#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ActionRequest; int /*<<< orphan*/  Installed; } ;
struct TYPE_5__ {scalar_t__ need_rollback; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIFEATURE ;
typedef  int /*<<< orphan*/  INSTALLSTATE ;

/* Variables and functions */

INSTALLSTATE msi_get_feature_action( MSIPACKAGE *package, MSIFEATURE *feature )
{
    if (package->need_rollback) return feature->Installed;
    return feature->ActionRequest;
}