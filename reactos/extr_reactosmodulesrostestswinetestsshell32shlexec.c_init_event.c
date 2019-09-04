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

/* Variables and functions */
 int /*<<< orphan*/  CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  hEvent ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void init_event(const char* child_file)
{
    char* event_name;
    event_name=strrchr(child_file, '\\')+1;
    hEvent=CreateEventA(NULL, FALSE, FALSE, event_name);
}