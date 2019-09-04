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
struct TYPE_3__ {int /*<<< orphan*/  KeyHandle; } ;
typedef  TYPE_1__* PLSA_DB_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  LsapRegDeleteSubKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
LsapDeleteObjectAttribute(PLSA_DB_OBJECT DbObject,
                          LPWSTR AttributeName)
{
    return LsapRegDeleteSubKey(DbObject->KeyHandle,
                               AttributeName);
}