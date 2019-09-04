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
typedef  int /*<<< orphan*/  TOOLBAR_INFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * GETDEFIMAGELIST (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETHIMLID (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline BOOL
TOOLBAR_IsValidImageList(const TOOLBAR_INFO *infoPtr, INT index)
{
    HIMAGELIST himl = GETDEFIMAGELIST(infoPtr, GETHIMLID(infoPtr, index));
    return (himl != NULL) && (ImageList_GetImageCount(himl) > 0);
}