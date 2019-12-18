#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int m_nXPos; int m_nYPos; int m_nZPos; } ;

/* Variables and functions */
 int m_nTotStars ; 
 TYPE_1__* stars ; 

void MoveStarField (int nXofs, int nYofs, int nZofs)
{
    int i;
    for (i = 0; i < m_nTotStars; i++)
    {
        stars[i].m_nXPos += nXofs;
        stars[i].m_nYPos += nYofs;
        stars[i].m_nZPos += nZofs;

        if (stars[i].m_nZPos > m_nTotStars)
            stars[i].m_nZPos -= m_nTotStars;
        if (stars[i].m_nZPos < 1)
            stars[i].m_nZPos += m_nTotStars;
    }
}