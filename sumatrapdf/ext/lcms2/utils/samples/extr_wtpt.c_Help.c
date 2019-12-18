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
 double LCMS_VERSION ; 
 int SW ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void Help(void)
{
       fprintf(stderr, "little CMS ICC white point utility - v3 [LittleCMS %2.2f]\n", LCMS_VERSION / 1000.0);

       fprintf(stderr, "usage: wtpt [flags] [<ICC profile>]\n\n");

       fprintf(stderr, "flags:\n\n");
       
       fprintf(stderr, "%cl - CIE Lab\n", SW);
       fprintf(stderr, "%cc - CIE LCh\n", SW);
       fprintf(stderr, "%cx - Don't show XYZ\n", SW);

       fprintf(stderr, "\nIf no parameters are given, then this program will\n");
       fprintf(stderr, "ask for XYZ value of media white. If parameter given, it must be\n");
       fprintf(stderr, "the profile to inspect.\n\n");

       fprintf(stderr, "This program is intended to be a demo of the little cms\n"
              "engine. Both lcms and this program are freeware. You can\n"
              "obtain both in source code at http://www.littlecms.com\n"
              "For suggestions, comments, bug reports etc. send mail to\n"
              "info@littlecms.com\n\n");
       exit(0);
}