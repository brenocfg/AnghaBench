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
struct TYPE_3__ {void* f; void* s; void* m; } ;
typedef  TYPE_1__ msf_t ;
typedef  int lsn_t ;

/* Variables and functions */
 int CDIO_CD_FRAMES_PER_MIN ; 
 int CDIO_CD_FRAMES_PER_SEC ; 
 int CDIO_CD_MAX_LSN ; 
 int CDIO_PREGAP_SECTORS ; 
 int /*<<< orphan*/  cdio_assert (int) ; 
 void* cdio_to_bcd8 (int) ; 
 int /*<<< orphan*/  cdio_warn (char*,int) ; 

void
cdio_lsn_to_msf (lsn_t lsn, msf_t *msf)
{
  int m, s, f;

  cdio_assert (msf != 0);

  if ( lsn >= -CDIO_PREGAP_SECTORS ){
    m    = (lsn + CDIO_PREGAP_SECTORS) / CDIO_CD_FRAMES_PER_MIN;
    lsn -= m * CDIO_CD_FRAMES_PER_MIN;
    s    = (lsn + CDIO_PREGAP_SECTORS) / CDIO_CD_FRAMES_PER_SEC;
    lsn -= s * CDIO_CD_FRAMES_PER_SEC;
    f    = lsn + CDIO_PREGAP_SECTORS;
  } else {
    m    = (lsn + CDIO_CD_MAX_LSN)     / CDIO_CD_FRAMES_PER_MIN;
    lsn -= m * (CDIO_CD_FRAMES_PER_MIN);
    s    = (lsn+CDIO_CD_MAX_LSN)       / CDIO_CD_FRAMES_PER_SEC;
    lsn -= s * CDIO_CD_FRAMES_PER_SEC;
    f    = lsn + CDIO_CD_MAX_LSN;
  }

  if (m > 99) {
    cdio_warn ("number of minutes (%d) truncated to 99.", m);
    m = 99;
  }

  msf->m = cdio_to_bcd8 (m);
  msf->s = cdio_to_bcd8 (s);
  msf->f = cdio_to_bcd8 (f);
}