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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Anime_GetFrameDelay (scalar_t__) ; 
 int /*<<< orphan*/  Anime_SetFrameIndex (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ m_nFrameCount ; 
 scalar_t__ m_nFrameIndex ; 
 scalar_t__ m_nLoopCount ; 
 scalar_t__ m_nLoopIndex ; 

BOOL Anime_Step(DWORD *pdwDelay)
{
    *pdwDelay = INFINITE;
    if (m_nLoopCount == (UINT)-1)
        return FALSE;

    if (m_nFrameIndex + 1 < m_nFrameCount)
    {
        *pdwDelay = Anime_GetFrameDelay(m_nFrameIndex);
        Anime_SetFrameIndex(m_nFrameIndex);
        ++m_nFrameIndex;
        return TRUE;
    }

    if (m_nLoopCount == 0 || m_nLoopIndex < m_nLoopCount)
    {
        *pdwDelay = Anime_GetFrameDelay(m_nFrameIndex);
        Anime_SetFrameIndex(m_nFrameIndex);
        m_nFrameIndex = 0;
        ++m_nLoopIndex;
        return TRUE;
    }

    return FALSE;
}