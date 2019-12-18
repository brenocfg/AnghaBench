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

/* Variables and functions */
 int /*<<< orphan*/  _ismbblead (unsigned char) ; 
 unsigned char _mbctolower (unsigned short) ; 
 unsigned char tolower (unsigned char) ; 

unsigned char * _mbslwr(unsigned char *x)
{
    unsigned char *y=x;

    if (x == NULL)
    {
        return NULL;
    }

    while (*y) 
    {
        if (!_ismbblead(*y)) 
        {
            *y = tolower(*y);
            y++;
        } 
        else
        {
            *y = _mbctolower(*(unsigned short *)y);
            y++;
        }
    }
    return x;
}