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
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 char* glGetString (int /*<<< orphan*/ ) ; 

int stbgl_hasExtension(char *ext)
{
   const char *s = glGetString(GL_EXTENSIONS);
   for(;;) {
      char *e = ext;
      for (;;) {
         if (*e == 0) {
            if (*s == 0 || *s == ' ') return 1;
            break;
         }
         if (*s != *e)
            break;
         ++s, ++e;
      }
      while (*s && *s != ' ') ++s;
      if (!*s) return 0;
      ++s; // skip space
   }
}