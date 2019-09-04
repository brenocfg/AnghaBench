#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_5__ {int /*<<< orphan*/ * Buffer; } ;
typedef  TYPE_1__* PUNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitEmptyUnicodeString (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup(PUNICODE_STRING String, WCHAR* Buffer, USHORT BufferSize)
{
    if (String->Buffer != Buffer)
    {
        RtlFreeUnicodeString(String);
        RtlInitEmptyUnicodeString(String, Buffer, BufferSize);
    }
}