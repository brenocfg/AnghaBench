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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void HelpLong(void) {
  printf("Usage: webpinfo [options] in_files\n"
         "Note: there could be multiple input files;\n"
         "      options must come before input files.\n"
         "Options:\n"
         "  -version ........... Print version number and exit.\n"
         "  -quiet ............. Do not show chunk parsing information.\n"
         "  -diag .............. Show parsing error diagnosis.\n"
         "  -summary ........... Show chunk stats summary.\n"
         "  -bitstream_info .... Parse bitstream header.\n");
}