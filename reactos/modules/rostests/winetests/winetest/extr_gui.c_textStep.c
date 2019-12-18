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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int progressCurr ; 
 int progressMax ; 
 int /*<<< orphan*/  stderr ; 
 char* vstrmake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
textStep (va_list ap)
{
    char *str = vstrmake (NULL, ap);

    progressCurr++;
    fputs (str, stderr);
    fprintf (stderr, " (%d of %d)\n", progressCurr, progressMax);
    free (str);
    return 0;
}