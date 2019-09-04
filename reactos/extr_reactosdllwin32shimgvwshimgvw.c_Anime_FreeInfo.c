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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ m_nFrameCount ; 
 scalar_t__ m_nFrameIndex ; 
 scalar_t__ m_nLoopCount ; 
 scalar_t__ m_nLoopIndex ; 
 int /*<<< orphan*/ * m_pDelayItem ; 

__attribute__((used)) static void Anime_FreeInfo(void)
{
    if (m_pDelayItem)
    {
        free(m_pDelayItem);
        m_pDelayItem = NULL;
    }
    m_nFrameIndex = 0;
    m_nFrameCount = 0;
    m_nLoopIndex = 0;
    m_nLoopCount = (UINT)-1;
}