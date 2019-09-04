#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * volume_label; } ;
typedef  TYPE_1__ MSIMEDIAINFO ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetVolumeInformationW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAddBackslashW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PathStripToRootW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL source_matches_volume(MSIMEDIAINFO *mi, LPCWSTR source_root)
{
    WCHAR volume_name[MAX_PATH + 1], root[MAX_PATH + 1];
    const WCHAR *p;
    int len, len2;

    strcpyW(root, source_root);
    PathStripToRootW(root);
    PathAddBackslashW(root);

    if (!GetVolumeInformationW(root, volume_name, MAX_PATH + 1, NULL, NULL, NULL, NULL, 0))
    {
        WARN("failed to get volume information for %s (%u)\n", debugstr_w(root), GetLastError());
        return FALSE;
    }

    len = strlenW( volume_name );
    len2 = strlenW( mi->volume_label );
    if (len2 > len) return FALSE;
    p = volume_name + len - len2;

    return !strcmpiW( mi->volume_label, p );
}