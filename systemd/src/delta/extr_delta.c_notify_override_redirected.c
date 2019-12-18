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
 int SHOW_REDIRECTED ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_ARROW ; 
 char* ansi_highlight () ; 
 char* ansi_normal () ; 
 int arg_flags ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char const*,char*,char const*) ; 
 char* special_glyph (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int notify_override_redirected(const char *top, const char *bottom) {
        if (!(arg_flags & SHOW_REDIRECTED))
                return 0;

        printf("%s%s%s %s %s %s\n",
               ansi_highlight(), "[REDIRECTED]", ansi_normal(),
               top, special_glyph(SPECIAL_GLYPH_ARROW), bottom);
        return 1;
}