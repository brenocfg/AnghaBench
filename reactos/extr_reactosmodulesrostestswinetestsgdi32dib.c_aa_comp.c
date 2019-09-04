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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  get_range (int,int,int*,int*) ; 

__attribute__((used)) static inline BYTE aa_comp(BYTE dst, BYTE text, BYTE alpha)
{
    BYTE min_comp, max_comp;

    if (alpha == 16)  return text;
    if (alpha <= 1)   return dst;
    if (text == dst)  return dst;

    get_range( alpha, text, &min_comp, &max_comp );

    if (dst > text)
    {
        DWORD diff = dst - text;
        DWORD range = max_comp - text;
        dst = text + (diff * range ) / (0xff - text);
        return dst;
    }
    else
    {
        DWORD diff = text - dst;
        DWORD range = text - min_comp ;
        dst = text - (diff * range) / text;
        return dst;
    }
}