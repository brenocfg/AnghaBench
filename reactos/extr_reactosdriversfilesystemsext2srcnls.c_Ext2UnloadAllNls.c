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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  UNLOAD_NLS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_nls_utf8 ; 

VOID
Ext2UnloadAllNls()
{

#ifdef FULL_CODEPAGES_SUPPORT

    UNLOAD_NLS(init_nls_ascii);
    UNLOAD_NLS(init_nls_cp1250);
    UNLOAD_NLS(exit_nls_cp1251);
    UNLOAD_NLS(exit_nls_cp1255);
    UNLOAD_NLS(exit_nls_cp437);
    UNLOAD_NLS(exit_nls_cp737);
    UNLOAD_NLS(exit_nls_cp775);
    UNLOAD_NLS(exit_nls_cp850);
    UNLOAD_NLS(exit_nls_cp852);
    UNLOAD_NLS(exit_nls_cp855);
    UNLOAD_NLS(exit_nls_cp857);
    UNLOAD_NLS(exit_nls_cp860);
    UNLOAD_NLS(exit_nls_cp861);
    UNLOAD_NLS(exit_nls_cp862);
    UNLOAD_NLS(exit_nls_cp863);
    UNLOAD_NLS(exit_nls_cp864);
    UNLOAD_NLS(exit_nls_cp865);
    UNLOAD_NLS(exit_nls_cp866);
    UNLOAD_NLS(exit_nls_cp869);
    UNLOAD_NLS(exit_nls_cp874);
    UNLOAD_NLS(exit_nls_euc_jp);
    UNLOAD_NLS(exit_nls_cp932);
    UNLOAD_NLS(exit_nls_cp949);
    UNLOAD_NLS(exit_nls_iso8859_1);
    UNLOAD_NLS(exit_nls_iso8859_13);
    UNLOAD_NLS(exit_nls_iso8859_14);
    UNLOAD_NLS(exit_nls_iso8859_15);
    UNLOAD_NLS(exit_nls_iso8859_2);
    UNLOAD_NLS(exit_nls_iso8859_3);
    UNLOAD_NLS(exit_nls_iso8859_4);
    UNLOAD_NLS(exit_nls_iso8859_5);
    UNLOAD_NLS(exit_nls_iso8859_6);
    UNLOAD_NLS(exit_nls_iso8859_7);
    UNLOAD_NLS(exit_nls_iso8859_9);
    UNLOAD_NLS(exit_nls_koi8_ru);
    UNLOAD_NLS(exit_nls_koi8_r);
    UNLOAD_NLS(exit_nls_koi8_u);

    /* unloading chinese codepages */
    UNLOAD_NLS(exit_nls_cp950);
    UNLOAD_NLS(exit_nls_cp936);

#endif //FULL_CODEPAGES_SUPPORT

    /* unloading nls of utf8  */
    UNLOAD_NLS(exit_nls_utf8);
}