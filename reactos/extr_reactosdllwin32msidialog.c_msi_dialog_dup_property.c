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
struct TYPE_5__ {TYPE_1__* package; } ;
typedef  TYPE_2__ msi_dialog ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR msi_dialog_dup_property( msi_dialog *dialog, LPCWSTR property, BOOL indirect )
{
    LPWSTR prop = NULL;

    if (!property)
        return NULL;

    if (indirect)
        prop = msi_dup_property( dialog->package->db, property );

    if (!prop)
        prop = strdupW( property );

    return prop;
}