#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char c; } ;
typedef  TYPE_1__ CPState ;

/* Variables and functions */
 char cp_get (TYPE_1__*) ; 
 scalar_t__ cp_iseol (char) ; 
 int /*<<< orphan*/  cp_newline (TYPE_1__*) ; 

__attribute__((used)) static void cp_comment_c(CPState *cp)
{
  do {
    if (cp_get(cp) == '*') {
      do {
	if (cp_get(cp) == '/') { cp_get(cp); return; }
      } while (cp->c == '*');
    }
    if (cp_iseol(cp->c)) cp_newline(cp);
  } while (cp->c != '\0');
}