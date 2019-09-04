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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void get_events(const char* name, HANDLE *start_event, HANDLE *done_event)
{
    const char* basename;
    char* event_name;

    basename=strrchr(name, '\\');
    basename=(basename ? basename+1 : name);
    event_name=HeapAlloc(GetProcessHeap(), 0, 6+strlen(basename)+1);

    sprintf(event_name, "start_%s", basename);
    *start_event=CreateEventA(NULL, 0,0, event_name);
    sprintf(event_name, "done_%s", basename);
    *done_event=CreateEventA(NULL, 0,0, event_name);
    HeapFree(GetProcessHeap(), 0, event_name);
}