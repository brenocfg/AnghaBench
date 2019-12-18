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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributesA (int /*<<< orphan*/  const*) ; 
 int INVALID_FILE_ATTRIBUTES ; 

__attribute__((used)) static BOOL dir_exists(const CHAR *name)
{
    DWORD attr;
    BOOL dir;

    attr = GetFileAttributesA(name);
    dir = ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);

    return ((attr != INVALID_FILE_ATTRIBUTES) && dir);
}