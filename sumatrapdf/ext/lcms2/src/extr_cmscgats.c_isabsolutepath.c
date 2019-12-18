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
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 char DIR_CHAR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static
cmsBool isabsolutepath(const char *path)
{
    char ThreeChars[4];

    if(path == NULL)
        return FALSE;
    if (path[0] == 0)
        return FALSE;

    strncpy(ThreeChars, path, 3);
    ThreeChars[3] = 0;

    if(ThreeChars[0] == DIR_CHAR)
        return TRUE;

#ifdef  CMS_IS_WINDOWS_
    if (isalpha((int) ThreeChars[0]) && ThreeChars[1] == ':')
        return TRUE;
#endif
    return FALSE;
}