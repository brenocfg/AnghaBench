#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dynamic; int /*<<< orphan*/  length; int /*<<< orphan*/ * stream; } ;
struct TYPE_8__ {TYPE_1__ string; } ;
struct TYPE_9__ {TYPE_2__ asnValue; int /*<<< orphan*/  asnType; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_3__ AsnAny ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SnmpUtilAsnAnyCpy (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static void setStringValue(AsnAny *value, BYTE type, DWORD len, BYTE *str)
{
    AsnAny strValue;

    strValue.asnType = type;
    strValue.asnValue.string.stream = str;
    strValue.asnValue.string.length = len;
    strValue.asnValue.string.dynamic = FALSE;
    SnmpUtilAsnAnyCpy(value, &strValue);
}