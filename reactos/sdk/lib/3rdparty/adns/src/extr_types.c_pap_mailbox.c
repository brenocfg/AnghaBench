#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* qu; } ;
typedef  TYPE_3__ parseinfo ;
typedef  int /*<<< orphan*/  adns_status ;
struct TYPE_8__ {TYPE_1__* typei; } ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
 int adns__qtf_mail822 ; 
 int /*<<< orphan*/  pap_domain (TYPE_3__ const*,int*,int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pap_mailbox822 (TYPE_3__ const*,int*,int,char**) ; 
 int /*<<< orphan*/  pdf_quoteok ; 

__attribute__((used)) static adns_status pap_mailbox(const parseinfo *pai, int *cbyte_io, int max,
			       char **mb_r) {
  if (pai->qu->typei->type & adns__qtf_mail822) {
    return pap_mailbox822(pai, cbyte_io, max, mb_r);
  } else {
    return pap_domain(pai, cbyte_io, max, mb_r, pdf_quoteok);
  }
}