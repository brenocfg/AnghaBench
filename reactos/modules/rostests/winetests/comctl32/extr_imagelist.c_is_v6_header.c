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
struct TYPE_3__ {int usVersion; } ;
typedef  TYPE_1__ ILHEAD ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL is_v6_header(const ILHEAD *header)
{
    return (header->usVersion & 0xff00) == 0x600;
}