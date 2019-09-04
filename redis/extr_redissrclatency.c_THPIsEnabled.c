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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

int THPIsEnabled(void) {
    char buf[1024];

    FILE *fp = fopen("/sys/kernel/mm/transparent_hugepage/enabled","r");
    if (!fp) return 0;
    if (fgets(buf,sizeof(buf),fp) == NULL) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return (strstr(buf,"[never]") == NULL) ? 1 : 0;
}