#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int i_symlink; char* psz_symlink; int i_symlink_max; } ;
struct TYPE_5__ {TYPE_1__ rr; } ;
typedef  TYPE_2__ iso9660_stat_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int const) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static bool
realloc_symlink(/*in/out*/ iso9660_stat_t *p_stat, uint8_t i_grow)
{
  if (!p_stat->rr.i_symlink) {
    const uint16_t i_max = 2*i_grow+1;
    p_stat->rr.psz_symlink = (char *) calloc(1, i_max);
    p_stat->rr.i_symlink_max = i_max;
    return (NULL != p_stat->rr.psz_symlink);
  } else {
    unsigned int i_needed = p_stat->rr.i_symlink + i_grow ;
    if ( i_needed <= p_stat->rr.i_symlink_max)
      return true;
    else {
      char * psz_newsymlink = (char *) calloc(1, 2*i_needed);
      if (!psz_newsymlink) return false;
      p_stat->rr.i_symlink_max = 2*i_needed;
      memcpy(psz_newsymlink, p_stat->rr.psz_symlink, p_stat->rr.i_symlink);
      free(p_stat->rr.psz_symlink);
      p_stat->rr.psz_symlink = psz_newsymlink;
      return true;
    }
  }
}