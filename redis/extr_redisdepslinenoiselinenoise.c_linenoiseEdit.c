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
struct linenoiseState {int ifd; int ofd; char* buf; size_t buflen; char const* prompt; scalar_t__ oldpos; scalar_t__ pos; int len; int /*<<< orphan*/  plen; scalar_t__ history_index; scalar_t__ maxrows; int /*<<< orphan*/  cols; } ;
typedef  int /*<<< orphan*/  linenoiseHintsCallback ;

/* Variables and functions */
#define  BACKSPACE 143 
#define  CTRL_A 142 
#define  CTRL_B 141 
#define  CTRL_C 140 
#define  CTRL_D 139 
#define  CTRL_E 138 
#define  CTRL_F 137 
#define  CTRL_K 136 
#define  CTRL_L 135 
#define  CTRL_N 134 
#define  CTRL_P 133 
#define  CTRL_T 132 
#define  CTRL_U 131 
#define  CTRL_W 130 
 int /*<<< orphan*/  EAGAIN ; 
#define  ENTER 129 
#define  ESC 128 
 int /*<<< orphan*/  LINENOISE_HISTORY_NEXT ; 
 int /*<<< orphan*/  LINENOISE_HISTORY_PREV ; 
 char completeLine (struct linenoiseState*) ; 
 int /*<<< orphan*/ * completionCallback ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getColumns (int,int) ; 
 int /*<<< orphan*/ * hintsCallback ; 
 int /*<<< orphan*/ * history ; 
 size_t history_len ; 
 int /*<<< orphan*/  linenoiseClearScreen () ; 
 int /*<<< orphan*/  linenoiseEditBackspace (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseEditDelete (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseEditDeletePrevWord (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseEditHistoryNext (struct linenoiseState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linenoiseEditInsert (struct linenoiseState*,char) ; 
 int /*<<< orphan*/  linenoiseEditMoveEnd (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseEditMoveHome (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseEditMoveLeft (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseEditMoveRight (struct linenoiseState*) ; 
 int /*<<< orphan*/  linenoiseHistoryAdd (char*) ; 
 int /*<<< orphan*/  mlmode ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  refreshLine (struct linenoiseState*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int linenoiseEdit(int stdin_fd, int stdout_fd, char *buf, size_t buflen, const char *prompt)
{
    struct linenoiseState l;

    /* Populate the linenoise state that we pass to functions implementing
     * specific editing functionalities. */
    l.ifd = stdin_fd;
    l.ofd = stdout_fd;
    l.buf = buf;
    l.buflen = buflen;
    l.prompt = prompt;
    l.plen = strlen(prompt);
    l.oldpos = l.pos = 0;
    l.len = 0;
    l.cols = getColumns(stdin_fd, stdout_fd);
    l.maxrows = 0;
    l.history_index = 0;

    /* Buffer starts empty. */
    l.buf[0] = '\0';
    l.buflen--; /* Make sure there is always space for the nulterm */

    /* The latest history entry is always our current buffer, that
     * initially is just an empty string. */
    linenoiseHistoryAdd("");

    if (write(l.ofd,prompt,l.plen) == -1) return -1;
    while(1) {
        char c;
        int nread;
        char seq[3];

        nread = read(l.ifd,&c,1);
        if (nread <= 0) return l.len;

        /* Only autocomplete when the callback is set. It returns < 0 when
         * there was an error reading from fd. Otherwise it will return the
         * character that should be handled next. */
        if (c == 9 && completionCallback != NULL) {
            c = completeLine(&l);
            /* Return on errors */
            if (c < 0) return l.len;
            /* Read next character when 0 */
            if (c == 0) continue;
        }

        switch(c) {
        case ENTER:    /* enter */
            history_len--;
            free(history[history_len]);
            if (mlmode) linenoiseEditMoveEnd(&l);
            if (hintsCallback) {
                /* Force a refresh without hints to leave the previous
                 * line as the user typed it after a newline. */
                linenoiseHintsCallback *hc = hintsCallback;
                hintsCallback = NULL;
                refreshLine(&l);
                hintsCallback = hc;
            }
            return (int)l.len;
        case CTRL_C:     /* ctrl-c */
            errno = EAGAIN;
            return -1;
        case BACKSPACE:   /* backspace */
        case 8:     /* ctrl-h */
            linenoiseEditBackspace(&l);
            break;
        case CTRL_D:     /* ctrl-d, remove char at right of cursor, or if the
                            line is empty, act as end-of-file. */
            if (l.len > 0) {
                linenoiseEditDelete(&l);
            } else {
                history_len--;
                free(history[history_len]);
                return -1;
            }
            break;
        case CTRL_T:    /* ctrl-t, swaps current character with previous. */
            if (l.pos > 0 && l.pos < l.len) {
                int aux = buf[l.pos-1];
                buf[l.pos-1] = buf[l.pos];
                buf[l.pos] = aux;
                if (l.pos != l.len-1) l.pos++;
                refreshLine(&l);
            }
            break;
        case CTRL_B:     /* ctrl-b */
            linenoiseEditMoveLeft(&l);
            break;
        case CTRL_F:     /* ctrl-f */
            linenoiseEditMoveRight(&l);
            break;
        case CTRL_P:    /* ctrl-p */
            linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_PREV);
            break;
        case CTRL_N:    /* ctrl-n */
            linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_NEXT);
            break;
        case ESC:    /* escape sequence */
            /* Read the next two bytes representing the escape sequence.
             * Use two calls to handle slow terminals returning the two
             * chars at different times. */
            if (read(l.ifd,seq,1) == -1) break;
            if (read(l.ifd,seq+1,1) == -1) break;

            /* ESC [ sequences. */
            if (seq[0] == '[') {
                if (seq[1] >= '0' && seq[1] <= '9') {
                    /* Extended escape, read additional byte. */
                    if (read(l.ifd,seq+2,1) == -1) break;
                    if (seq[2] == '~') {
                        switch(seq[1]) {
                        case '3': /* Delete key. */
                            linenoiseEditDelete(&l);
                            break;
                        }
                    }
                } else {
                    switch(seq[1]) {
                    case 'A': /* Up */
                        linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_PREV);
                        break;
                    case 'B': /* Down */
                        linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_NEXT);
                        break;
                    case 'C': /* Right */
                        linenoiseEditMoveRight(&l);
                        break;
                    case 'D': /* Left */
                        linenoiseEditMoveLeft(&l);
                        break;
                    case 'H': /* Home */
                        linenoiseEditMoveHome(&l);
                        break;
                    case 'F': /* End*/
                        linenoiseEditMoveEnd(&l);
                        break;
                    }
                }
            }

            /* ESC O sequences. */
            else if (seq[0] == 'O') {
                switch(seq[1]) {
                case 'H': /* Home */
                    linenoiseEditMoveHome(&l);
                    break;
                case 'F': /* End*/
                    linenoiseEditMoveEnd(&l);
                    break;
                }
            }
            break;
        default:
            if (linenoiseEditInsert(&l,c)) return -1;
            break;
        case CTRL_U: /* Ctrl+u, delete the whole line. */
            buf[0] = '\0';
            l.pos = l.len = 0;
            refreshLine(&l);
            break;
        case CTRL_K: /* Ctrl+k, delete from current to end of line. */
            buf[l.pos] = '\0';
            l.len = l.pos;
            refreshLine(&l);
            break;
        case CTRL_A: /* Ctrl+a, go to the start of the line */
            linenoiseEditMoveHome(&l);
            break;
        case CTRL_E: /* ctrl+e, go to the end of the line */
            linenoiseEditMoveEnd(&l);
            break;
        case CTRL_L: /* ctrl+l, clear screen */
            linenoiseClearScreen();
            refreshLine(&l);
            break;
        case CTRL_W: /* ctrl+w, delete previous word */
            linenoiseEditDeletePrevWord(&l);
            break;
        }
    }
    return l.len;
}