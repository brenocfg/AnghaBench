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
typedef  int WORD ;

/* Variables and functions */
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static WORD SLTG_ReadStringA(const char *ptr, char **str)
{
    WORD bytelen;

    *str = NULL;
    bytelen = *(const WORD*)ptr;
    if(bytelen == 0xffff) return 2;
    *str = heap_alloc(bytelen + 1);
    memcpy(*str, ptr + 2, bytelen);
    (*str)[bytelen] = '\0';
    return bytelen + 2;
}