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
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static
BOOL unserialize_dword(const BYTE *ptr, DWORD *index, DWORD size, DWORD *value)
{
    /*TRACE("called\n");*/

    if (!ptr || !index || !value) return FALSE;

    if (*index+sizeof(DWORD)>size)
    {
        return FALSE;
    }

    memcpy(value,&(ptr[*index]),sizeof(DWORD));
    *index+=sizeof(DWORD);

    return TRUE;
}