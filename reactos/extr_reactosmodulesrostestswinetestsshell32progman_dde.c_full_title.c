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
typedef  int /*<<< orphan*/  cs ;
struct TYPE_4__ {int fFullPathTitle; } ;
typedef  TYPE_1__ CABINETSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ReadCabinetState (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL full_title(void)
{
    CABINETSTATE cs;

    memset(&cs, 0, sizeof(cs));
    ReadCabinetState(&cs, sizeof(cs));

    return (cs.fFullPathTitle == -1);
}