#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ tgl_peer_t ;
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct username_peer_pair {TYPE_1__* peer; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int TGL_PEER_CHANNEL ; 
 int TGL_PEER_CHAT ; 
 int TGL_PEER_ENCR_CHAT ; 
 int /*<<< orphan*/  TGL_PEER_NOT_FOUND ; 
 int TGL_PEER_USER ; 
 int /*<<< orphan*/  TLS ; 
 int atoi (char*) ; 
 int hex2int (char const) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tfree_str (char*) ; 
 int tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 TYPE_2__* tgl_peer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tgl_peer_get_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tgl_set_peer_id (int,int) ; 
 struct username_peer_pair* tree_lookup_username_peer_pair (int /*<<< orphan*/ ,void*) ; 
 char* tstrndup (char const*,int) ; 
 int /*<<< orphan*/  username_peer_pair ; 

tgl_peer_id_t parse_input_peer_id (const char *s, int l, int mask) {
  if (!s || l <= 0) { return TGL_PEER_NOT_FOUND; }

  if (*s == '$') {
    s ++;
    l --;
    if (l != 2 * sizeof (tgl_peer_id_t)) {
      return TGL_PEER_NOT_FOUND;
    }

    tgl_peer_id_t res;
    unsigned char *r = (void *)&res;
    int i;
    for (i = 0; i < l; i++) {
      if ((s[i] < '0' || s[i] > '9') && 
          (s[i] < 'a' || s[i] > 'f')) {
        return TGL_PEER_NOT_FOUND;
      }
    }
    for (i = 0; i < (int)sizeof (tgl_peer_id_t); i++) {
      r[i] = hex2int (s[2 * i]) * 16 + hex2int (s[2 * i + 1]);
    }

    if (mask && tgl_get_peer_type (res) != mask) {
      return TGL_PEER_NOT_FOUND;
    }

    return res;
  }

  if (*s == '@') {
    s ++;
    l --;
    char *tmp = tstrndup (s, l);
    struct username_peer_pair *p = tree_lookup_username_peer_pair (username_peer_pair, (void *)&tmp);
    tfree_str (tmp);
    if (p && (!mask || tgl_get_peer_type (p->peer->id) == mask)) {
      return p->peer->id;
    } else {
      return TGL_PEER_NOT_FOUND;
    }
  }

  const char *ss[] = {"user#id", "user#", "chat#id", "chat#", "secret_chat#id", "secret_chat#", "channel#id", "channel#"};
  int tt[] = {TGL_PEER_USER, TGL_PEER_USER, TGL_PEER_CHAT, TGL_PEER_CHAT, TGL_PEER_ENCR_CHAT, TGL_PEER_ENCR_CHAT, TGL_PEER_CHANNEL, TGL_PEER_CHANNEL};

  char *sc = tstrndup (s, l);

  int i;
  for (i = 0; i < 8; i++) if (!mask || mask == tt[i]) {
    int x = strlen (ss[i]);
    if (l > x && !memcmp (s, ss[i], x)) {
      int r = atoi (sc + x);
      tfree_str (sc);
      if (r < 0) { return TGL_PEER_NOT_FOUND; }
      tgl_peer_t *P = tgl_peer_get (TLS, tgl_set_peer_id (tt[i], r));
      if (!P) { return TGL_PEER_NOT_FOUND; }
      return P->id;
    }
  }

  tgl_peer_t *P = tgl_peer_get_by_name (TLS, sc); 
  tfree_str (sc);
  
  if (P && (!mask || tgl_get_peer_type (P->id) == mask)) {
    return P->id;
  } else {
    return TGL_PEER_NOT_FOUND;
  }
}