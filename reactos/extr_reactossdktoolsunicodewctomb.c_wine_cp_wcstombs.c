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
struct TYPE_2__ {int char_size; } ;
union cptable {int /*<<< orphan*/  dbcs; int /*<<< orphan*/  sbcs; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int get_length_dbcs (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,char const*,int*) ; 
 int get_length_sbcs (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int*) ; 
 int wcstombs_dbcs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,char*,int) ; 
 int wcstombs_dbcs_slow (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,char*,int,char const*,int*) ; 
 int wcstombs_sbcs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,char*,int) ; 
 int wcstombs_sbcs_slow (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,char*,int,char const*,int*) ; 

int wine_cp_wcstombs( const union cptable *table, int flags,
                      const WCHAR *src, int srclen,
                      char *dst, int dstlen, const char *defchar, int *used )
{
    if (table->info.char_size == 1)
    {
        if (flags || defchar || used)
        {
            if (!dstlen) return get_length_sbcs( &table->sbcs, flags, src, srclen, used );
            return wcstombs_sbcs_slow( &table->sbcs, flags, src, srclen,
                                       dst, dstlen, defchar, used );
        }
        if (!dstlen) return srclen;
        return wcstombs_sbcs( &table->sbcs, src, srclen, dst, dstlen );
    }
    else /* mbcs */
    {
        if (!dstlen) return get_length_dbcs( &table->dbcs, flags, src, srclen, defchar, used );
        if (flags || defchar || used)
            return wcstombs_dbcs_slow( &table->dbcs, flags, src, srclen,
                                       dst, dstlen, defchar, used );
        return wcstombs_dbcs( &table->dbcs, src, srclen, dst, dstlen );
    }
}