#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ m_nXPos; scalar_t__ m_nYPos; int m_nZPos; int m_nOldX; int m_nOldY; } ;
typedef  TYPE_1__ STAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_STARS ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* RANDOM (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int m_nTotStars ; 
 scalar_t__ malloc (int) ; 
 TYPE_1__* stars ; 

BOOL SetUpStars (int nNumStars)
{
    int i;
    if (nNumStars > MAX_STARS)
    {
        MessageBox (0,
            _T("Too many stars! Aborting!"),
            _T("Error"),
            MB_OK | MB_ICONWARNING);
        return FALSE;
    }

    if (stars)
        free (stars);

    m_nTotStars = nNumStars;

    stars = (STAR*)malloc(nNumStars * sizeof(STAR));

    if (!stars)
    {
        MessageBox (0,
            _T("Unable to allocate memory! Aborting!"),
            _T("Error"),
            MB_OK | MB_ICONWARNING);
        return FALSE;
    }

    for (i = 0; i < m_nTotStars; i++)
    {
        do
        {
            stars[i].m_nXPos = RANDOM (-320, 320);
            stars[i].m_nYPos = RANDOM (-200, 200);
            stars[i].m_nZPos = i+1;
            stars[i].m_nOldX = -1;
            stars[i].m_nOldY = -1;
        } while ((stars[i].m_nXPos == 0) || (stars[i].m_nYPos == 0));
    }
    return TRUE;
}