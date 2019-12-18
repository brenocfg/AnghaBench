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
typedef  int /*<<< orphan*/  cmsInfoType ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int cmsGetProfileInfoASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static
void PrintInfo(cmsContext ContextID, cmsHPROFILE h, cmsInfoType Info)
{
    char* text;
    int len;

    len = cmsGetProfileInfoASCII(ContextID, h, Info, "en", "US", NULL, 0);
    if (len == 0) return;

    text = (char*) malloc(len * sizeof(char));
    if (text == NULL) return;

    cmsGetProfileInfoASCII(ContextID, h, Info, "en", "US", text, len);

    if (strlen(text) > 0)
        printf("%s\n", text);

    free(text);
}