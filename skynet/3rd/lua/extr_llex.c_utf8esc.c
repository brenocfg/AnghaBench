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
typedef  int /*<<< orphan*/  LexState ;

/* Variables and functions */
 int UTF8BUFFSZ ; 
 int luaO_utf8esc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readutf8esc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void utf8esc (LexState *ls) {
  char buff[UTF8BUFFSZ];
  int n = luaO_utf8esc(buff, readutf8esc(ls));
  for (; n > 0; n--)  /* add 'buff' to string */
    save(ls, buff[UTF8BUFFSZ - n]);
}