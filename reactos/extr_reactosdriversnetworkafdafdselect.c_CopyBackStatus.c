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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t UINT ;
struct TYPE_3__ {scalar_t__ Status; scalar_t__ Events; } ;
typedef  TYPE_1__* PAFD_HANDLE ;

/* Variables and functions */

__attribute__((used)) static VOID CopyBackStatus( PAFD_HANDLE HandleArray,
                            UINT HandleCount ) {
    UINT i;

    for( i = 0; i < HandleCount; i++ ) {
        HandleArray[i].Events = HandleArray[i].Status;
        HandleArray[i].Status = 0;
    }
}