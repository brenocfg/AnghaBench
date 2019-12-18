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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  TAGREF ;

/* Variables and functions */
 int /*<<< orphan*/  SDB_DATABASE_MAIN_SHIM ; 
 scalar_t__ g_LayerDB ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSdbGetLayerTagRef (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ pSdbInitDatabase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

TAGREF find_layer(const char* szLayerStart, const char* szLayerEnd)
{
    char layer[100] = { 0 };
    WCHAR layerW[100] = { 0 };
    strncpy(layer, szLayerStart, szLayerEnd - szLayerStart);

    if (!g_LayerDB)
    {
        g_LayerDB = pSdbInitDatabase(SDB_DATABASE_MAIN_SHIM, 0);
    }

    mbstowcs(layerW, layer, strlen(layer));
    return pSdbGetLayerTagRef(g_LayerDB, layerW);
}