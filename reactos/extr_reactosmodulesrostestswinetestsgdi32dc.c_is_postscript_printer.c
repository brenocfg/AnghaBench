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
typedef  int /*<<< orphan*/  tech ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ExtEscape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  GETTECHNOLOGY ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static BOOL is_postscript_printer(HDC hdc)
{
    char tech[256];

    if (ExtEscape(hdc, GETTECHNOLOGY, 0, NULL, sizeof(tech), tech) > 0)
        return strcmp(tech, "PostScript") == 0;

    return FALSE;
}