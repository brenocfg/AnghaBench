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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  getdelim (char**,size_t*,char,int /*<<< orphan*/ *) ; 

ssize_t getline (char **restrict lineptr, size_t *restrict n,
                 FILE *restrict stream)
{
    return getdelim (lineptr, n, '\n', stream);
}