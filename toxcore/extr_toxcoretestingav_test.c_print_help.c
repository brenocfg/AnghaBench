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
 int /*<<< orphan*/  printf (char*,char const*) ; 

int print_help (const char *name)
{
    printf("Usage: %s -[a:v:o:dh]\n"
           "-a <path> audio input file\n"
           "-b <ms> audio frame duration\n"
           "-v <path> video input file\n"
           "-x <ms> video frame duration\n"
           "-o <idx> output audio device index\n"
           "-d print output audio devices\n"
           "-h print this help\n", name);

    return 0;
}