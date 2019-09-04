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
 int DEBUGLEVEL_CHAT ; 
 int DEBUGLEVEL_TRACE ; 
 int /*<<< orphan*/  chat (char*,int) ; 
 int debuglevel ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void dump_var_desc(const char *data, int size)
{
    const unsigned char *p = (const unsigned char *)data;
    int i;

    if (!(debuglevel & (DEBUGLEVEL_TRACE | DEBUGLEVEL_CHAT))) return;

    chat("dump_var_desc: size %d bytes\n", size);

    for (i = 0; i < size; i++)
        fprintf(stderr, " %02x", *p++);

    fprintf(stderr, "\n");
}