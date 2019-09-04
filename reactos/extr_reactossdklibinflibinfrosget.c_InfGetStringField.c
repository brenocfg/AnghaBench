#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/  PINFCONTEXT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  INF_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpGetStringField (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN
InfGetStringField(PINFCONTEXT Context,
                  ULONG FieldIndex,
                  PWSTR ReturnBuffer,
                  ULONG ReturnBufferSize,
                  PULONG RequiredSize)
{
  return INF_SUCCESS(InfpGetStringField(Context, FieldIndex, ReturnBuffer,
                                        ReturnBufferSize, RequiredSize));
}