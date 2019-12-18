#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int year; int month; int day; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; } ;
struct TYPE_4__ {TYPE_1__ date_and_time; } ;

/* Variables and functions */
 TYPE_2__ root ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_time_string(char *str)
{
    sprintf(str, "%04d%02d%02d%02d%02d%02d00",
            root.date_and_time.year,
            root.date_and_time.month,
            root.date_and_time.day,
            root.date_and_time.hour,
            root.date_and_time.minute,
            root.date_and_time.second);
}