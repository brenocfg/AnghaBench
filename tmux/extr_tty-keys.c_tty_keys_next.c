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
typedef  int u_char ;
struct TYPE_2__ {int* c_cc; } ;
struct tty {int flags; int /*<<< orphan*/  in; struct client* client; int /*<<< orphan*/  key_timer; TYPE_1__ tio; } ;
struct timeval {int tv_sec; int tv_usec; } ;
struct mouse_event {int /*<<< orphan*/  member_0; } ;
struct key_event {int key; int /*<<< orphan*/  m; } ;
struct client {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
typedef  int key_code ;
typedef  int cc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_FOCUSED ; 
 char* EVBUFFER_DATA (int /*<<< orphan*/ ) ; 
 size_t EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 int KEYC_BSPACE ; 
 int KEYC_ESCAPE ; 
 int KEYC_FOCUS_IN ; 
 int KEYC_FOCUS_OUT ; 
 int KEYC_MASK_KEY ; 
 int KEYC_MASK_MOD ; 
 int KEYC_MOUSE ; 
 int KEYC_UNKNOWN ; 
 int KEYC_XTERM ; 
 int TTY_TIMER ; 
 size_t VERASE ; 
 int _POSIX_VDISABLE ; 
 int /*<<< orphan*/  evbuffer_drain (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 scalar_t__ evtimer_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  free (struct key_event*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mouse_event*,int) ; 
 int options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  server_client_handle_key (struct client*,struct key_event*) ; 
 int /*<<< orphan*/  tty_keys_callback ; 
 int tty_keys_clipboard (struct tty*,char const*,size_t,size_t*) ; 
 int tty_keys_device_attributes (struct tty*,char const*,size_t,size_t*) ; 
 int tty_keys_mouse (struct tty*,char const*,size_t,size_t*,struct mouse_event*) ; 
 int tty_keys_next1 (struct tty*,char const*,size_t,int*,size_t*,int) ; 
 struct key_event* xmalloc (int) ; 

int
tty_keys_next(struct tty *tty)
{
	struct client		*c = tty->client;
	struct timeval		 tv;
	const char		*buf;
	size_t			 len, size;
	cc_t			 bspace;
	int			 delay, expired = 0, n;
	key_code		 key;
	struct mouse_event	 m = { 0 };
	struct key_event	*event;

	gettimeofday(&tv, NULL);

	/* Get key buffer. */
	buf = EVBUFFER_DATA(tty->in);
	len = EVBUFFER_LENGTH(tty->in);
	if (len == 0)
		return (0);
	log_debug("%s: keys are %zu (%.*s)", c->name, len, (int)len, buf);

	/* Is this a clipboard response? */
	switch (tty_keys_clipboard(tty, buf, len, &size)) {
	case 0:		/* yes */
		key = KEYC_UNKNOWN;
		goto complete_key;
	case -1:	/* no, or not valid */
		break;
	case 1:		/* partial */
		goto partial_key;
	}

	/* Is this a device attributes response? */
	switch (tty_keys_device_attributes(tty, buf, len, &size)) {
	case 0:		/* yes */
		key = KEYC_UNKNOWN;
		goto complete_key;
	case -1:	/* no, or not valid */
		break;
	case 1:		/* partial */
		goto partial_key;
	}

	/* Is this a mouse key press? */
	switch (tty_keys_mouse(tty, buf, len, &size, &m)) {
	case 0:		/* yes */
		key = KEYC_MOUSE;
		goto complete_key;
	case -1:	/* no, or not valid */
		break;
	case -2:	/* yes, but we don't care. */
		key = KEYC_MOUSE;
		goto discard_key;
	case 1:		/* partial */
		goto partial_key;
	}

first_key:
	/* Try to lookup complete key. */
	n = tty_keys_next1(tty, buf, len, &key, &size, expired);
	if (n == 0)	/* found */
		goto complete_key;
	if (n == 1)
		goto partial_key;

	/*
	 * If not a complete key, look for key with an escape prefix (meta
	 * modifier).
	 */
	if (*buf == '\033' && len > 1) {
		/* Look for a key without the escape. */
		n = tty_keys_next1(tty, buf + 1, len - 1, &key, &size, expired);
		if (n == 0) {	/* found */
			if (key & KEYC_XTERM) {
				/*
				 * We want the escape key as well as the xterm
				 * key, because the xterm sequence implicitly
				 * includes the escape (so if we see
				 * \033\033[1;3D we know it is an Escape
				 * followed by M-Left, not just M-Left).
				 */
				key = '\033';
				size = 1;
				goto complete_key;
			}
			key |= KEYC_ESCAPE;
			size++;
			goto complete_key;
		}
		if (n == 1)	/* partial */
			goto partial_key;
	}

	/*
	 * At this point, we know the key is not partial (with or without
	 * escape). So pass it through even if the timer has not expired.
	 */
	if (*buf == '\033' && len >= 2) {
		key = (u_char)buf[1] | KEYC_ESCAPE;
		size = 2;
	} else {
		key = (u_char)buf[0];
		size = 1;
	}
	goto complete_key;

partial_key:
	log_debug("%s: partial key %.*s", c->name, (int)len, buf);

	/* If timer is going, check for expiration. */
	if (tty->flags & TTY_TIMER) {
		if (evtimer_initialized(&tty->key_timer) &&
		    !evtimer_pending(&tty->key_timer, NULL)) {
			expired = 1;
			goto first_key;
		}
		return (0);
	}

	/* Get the time period. */
	delay = options_get_number(global_options, "escape-time");
	tv.tv_sec = delay / 1000;
	tv.tv_usec = (delay % 1000) * 1000L;

	/* Start the timer. */
	if (event_initialized(&tty->key_timer))
		evtimer_del(&tty->key_timer);
	evtimer_set(&tty->key_timer, tty_keys_callback, tty);
	evtimer_add(&tty->key_timer, &tv);

	tty->flags |= TTY_TIMER;
	return (0);

complete_key:
	log_debug("%s: complete key %.*s %#llx", c->name, (int)size, buf, key);

	/*
	 * Check for backspace key using termios VERASE - the terminfo
	 * kbs entry is extremely unreliable, so cannot be safely
	 * used. termios should have a better idea.
	 */
	bspace = tty->tio.c_cc[VERASE];
	if (bspace != _POSIX_VDISABLE && (key & KEYC_MASK_KEY) == bspace)
		key = (key & KEYC_MASK_MOD) | KEYC_BSPACE;

	/* Remove data from buffer. */
	evbuffer_drain(tty->in, size);

	/* Remove key timer. */
	if (event_initialized(&tty->key_timer))
		evtimer_del(&tty->key_timer);
	tty->flags &= ~TTY_TIMER;

	/* Check for focus events. */
	if (key == KEYC_FOCUS_OUT) {
		tty->client->flags &= ~CLIENT_FOCUSED;
		return (1);
	} else if (key == KEYC_FOCUS_IN) {
		tty->client->flags |= CLIENT_FOCUSED;
		return (1);
	}

	/* Fire the key. */
	if (key != KEYC_UNKNOWN) {
		event = xmalloc(sizeof *event);
		event->key = key;
		memcpy(&event->m, &m, sizeof event->m);
		if (!server_client_handle_key(c, event))
			free(event);
	}

	return (1);

discard_key:
	log_debug("%s: discard key %.*s %#llx", c->name, (int)size, buf, key);

	/* Remove data from buffer. */
	evbuffer_drain(tty->in, size);

	return (1);
}