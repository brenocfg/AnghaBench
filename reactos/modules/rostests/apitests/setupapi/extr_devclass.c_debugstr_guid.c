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
typedef  int /*<<< orphan*/  guidSTR1 ;
struct TYPE_3__ {int /*<<< orphan*/ * Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ GUID ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *debugstr_guid(const GUID *guid)
{
    static char guidSTR1[39];
    static char guidSTR2[39];
    char* guidSTR;
    static BOOL index;

    if (!guid) return NULL;

    index = !index;
    guidSTR = index ? guidSTR1 : guidSTR2;

    snprintf(guidSTR, sizeof(guidSTR1),
     "{%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
     guid->Data1, guid->Data2, guid->Data3,
     guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3],
     guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]);
    return guidSTR;
}