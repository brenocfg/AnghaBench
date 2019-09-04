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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  PUCHAR ;

/* Variables and functions */
 scalar_t__ ISAPNP_WRITE_DATA ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
inline
VOID
WriteData(USHORT Data)
{
  WRITE_PORT_UCHAR((PUCHAR)ISAPNP_WRITE_DATA, Data);
}