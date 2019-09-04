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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  serialize_dword (int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static
void serialize_string(const BYTE *str, BYTE **ptr, DWORD len, DWORD width,
                      BOOL prepend_len)
{
    /*TRACE("called %ux%u\n",(unsigned int)len,(unsigned int)width);*/

    if (prepend_len)
    {
        serialize_dword(len,ptr);
    }
    memcpy(*ptr,str,len*width);
    *ptr+=len*width;
}