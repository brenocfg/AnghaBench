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
struct TYPE_2__ {int m_nOldX; int m_nOldY; scalar_t__ m_nZPos; scalar_t__ m_nYPos; scalar_t__ m_nXPos; } ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetPixel (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ m_nCenterX ; 
 scalar_t__ m_nCenterY ; 
 int m_nTotStars ; 
 TYPE_1__* stars ; 

void DrawStarField (HDC pDC)
{
    int nX, nY;
    int i;
    for (i = 0; i < m_nTotStars; i++)
    {
        // Clear last position of this star
        SetPixel (
            pDC,
            stars[i].m_nOldX,
            stars[i].m_nOldY,
            RGB (0, 0, 0));

        nX = (int)((((long)stars[i].m_nXPos << 7) / (long)stars[i].m_nZPos) + m_nCenterX);
        nY = (int)((((long)stars[i].m_nYPos << 7) / (long)stars[i].m_nZPos) + m_nCenterY);

        // Draw star
        SetPixel (
            pDC,
            nX,
            nY,
            RGB (255, 255, 255));

        // Remember current position for clearing later
        stars[i].m_nOldX = nX;
        stars[i].m_nOldY = nY;
    }
}