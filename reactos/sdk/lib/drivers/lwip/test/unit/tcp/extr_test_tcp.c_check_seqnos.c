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
typedef  int /*<<< orphan*/  u32_t ;
struct tcp_seg {TYPE_1__* tcphdr; struct tcp_seg* next; } ;
struct TYPE_2__ {scalar_t__ seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_RET (int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_seqnos(struct tcp_seg *segs, int num_expected, u32_t *seqnos_expected)
{
  struct tcp_seg *s = segs;
  int i;
  for (i = 0; i < num_expected; i++, s = s->next) {
    EXPECT_RET(s != NULL);
    EXPECT(s->tcphdr->seqno == htonl(seqnos_expected[i]));
  }
  EXPECT(s == NULL);
}