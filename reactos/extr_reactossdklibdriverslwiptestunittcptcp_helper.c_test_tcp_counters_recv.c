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
struct test_tcp_counters {scalar_t__ close_calls; scalar_t__ recv_calls_after_close; scalar_t__ recved_bytes_after_close; int /*<<< orphan*/  recved_bytes; int /*<<< orphan*/  recv_calls; } ;
struct tcp_pcb {int dummy; } ;
struct pbuf {scalar_t__ tot_len; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_RETX (int,scalar_t__) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  test_tcp_counters_check_rxdata (struct test_tcp_counters*,struct pbuf*) ; 

err_t
test_tcp_counters_recv(void* arg, struct tcp_pcb* pcb, struct pbuf* p, err_t err)
{
  struct test_tcp_counters* counters = arg;
  EXPECT_RETX(arg != NULL, ERR_OK);
  EXPECT_RETX(pcb != NULL, ERR_OK);
  EXPECT_RETX(err == ERR_OK, ERR_OK);

  if (p != NULL) {
    if (counters->close_calls == 0) {
      counters->recv_calls++;
      test_tcp_counters_check_rxdata(counters, p);
      counters->recved_bytes += p->tot_len;
    } else {
      counters->recv_calls_after_close++;
      counters->recved_bytes_after_close += p->tot_len;
    }
    pbuf_free(p);
  } else {
    counters->close_calls++;
  }
  EXPECT(counters->recv_calls_after_close == 0 && counters->recved_bytes_after_close == 0);
  return ERR_OK;
}