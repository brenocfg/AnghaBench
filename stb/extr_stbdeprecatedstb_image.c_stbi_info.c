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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int e (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int stbi_info_from_file (int /*<<< orphan*/ *,int*,int*,int*) ; 

int stbi_info(char const *filename, int *x, int *y, int *comp)
{
    FILE *f = fopen(filename, "rb");
    int result;
    if (!f) return e("can't fopen", "Unable to open file");
    result = stbi_info_from_file(f, x, y, comp);
    fclose(f);
    return result;
}