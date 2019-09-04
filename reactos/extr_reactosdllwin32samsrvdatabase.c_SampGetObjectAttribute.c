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
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_1__* PSAM_DB_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  SampRegQueryValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
SampGetObjectAttribute(PSAM_DB_OBJECT DbObject,
                       LPWSTR AttributeName,
                       PULONG AttributeType,
                       LPVOID AttributeData,
                       PULONG AttributeSize)
{
    return SampRegQueryValue(DbObject->KeyHandle,
                             AttributeName,
                             AttributeType,
                             AttributeData,
                             AttributeSize);
}