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
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct tgl_message {int flags; int /*<<< orphan*/  to_id; int /*<<< orphan*/  from_id; } ;
struct in_ev {int dummy; } ;
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  our_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int TGLMF_OUT ; 
#define  TGL_PEER_CHAT 130 
#define  TGL_PEER_ENCR_CHAT 129 
#define  TGL_PEER_USER 128 
 TYPE_1__* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ enable_json ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_pack_read (struct tgl_message*) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,...) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 struct in_ev* notify_ev ; 
 int /*<<< orphan*/  print_chat_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_encr_chat_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_user_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_cmp_peer_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_peer_get (TYPE_1__*,int /*<<< orphan*/ ) ; 

void print_read_list (int num, struct tgl_message *list[]) {
  struct in_ev *ev = notify_ev;
  int i;
  mprint_start (ev);
  for (i = 0; i < num; i++) if (list[i]) {
    if (enable_json) {
      #ifdef USE_JSON
        json_t *res = json_pack_read (list[i]);
        char *s = json_dumps (res, 0);
        mprintf (ev, "%s\n", s);
        json_decref (res);
        free (s);
      #endif
    }
    tgl_peer_id_t to_id;
    if (!tgl_cmp_peer_id (list[i]->to_id, TLS->our_id)) {
      to_id = list[i]->from_id;
    } else {
      to_id = list[i]->to_id;
    }
    int j;
    int c1 = 0;
    int c2 = 0;
    for (j = i; j < num; j++) if (list[j]) {
      tgl_peer_id_t end_id;
      if (!tgl_cmp_peer_id (list[j]->to_id, TLS->our_id)) {
        end_id = list[j]->from_id;
      } else {
        end_id = list[j]->to_id;
      }
      if (!tgl_cmp_peer_id (to_id, end_id)) {
        if (list[j]->flags & TGLMF_OUT) {
          c1 ++;
        } else {
          c2 ++;
        }
        list[j] = 0;
      }
    }

    assert (c1 + c2 > 0);
    if (!enable_json)  {
      mpush_color (ev, COLOR_YELLOW);
      switch (tgl_get_peer_type (to_id)) {
      case TGL_PEER_USER:
        mprintf (ev, "User ");
        print_user_name (ev, to_id, tgl_peer_get (TLS, to_id));
        break;
      case TGL_PEER_CHAT:
        mprintf (ev, "Chat ");
        print_chat_name (ev, to_id, tgl_peer_get (TLS, to_id));
        break;
      case TGL_PEER_ENCR_CHAT:
        mprintf (ev, "Secret chat ");
        print_encr_chat_name (ev, to_id, tgl_peer_get (TLS, to_id));
        break;
      default:
        assert (0);
      }
      mprintf (ev, " marked read %d outbox and %d inbox messages\n", c1, c2);
      mpop_color (ev);
    }
  }
  mprint_end (ev);
}