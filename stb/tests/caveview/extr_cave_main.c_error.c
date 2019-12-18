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
 int /*<<< orphan*/  SDL_MESSAGEBOX_ERROR ; 
 int /*<<< orphan*/  SDL_ShowSimpleMessageBox (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

void error(char *s)
{
   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", s, NULL);
   exit(0);
}