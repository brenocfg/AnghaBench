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
struct sequence {double max; double min; scalar_t__ labels; struct sample* samples; } ;
struct sample {double value; char* label; } ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int SPARKLINE_FILL ; 
 int SPARKLINE_LOG_SCALE ; 
 char* charset ; 
 char* charset_fill ; 
 int charset_len ; 
 int label_margin_top ; 
 double log (double) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zfree (char*) ; 
 char* zmalloc (int) ; 

sds sparklineRenderRange(sds output, struct sequence *seq, int rows, int offset, int len, int flags) {
    int j;
    double relmax = seq->max - seq->min;
    int steps = charset_len*rows;
    int row = 0;
    char *chars = zmalloc(len);
    int loop = 1;
    int opt_fill = flags & SPARKLINE_FILL;
    int opt_log = flags & SPARKLINE_LOG_SCALE;

    if (opt_log) {
        relmax = log(relmax+1);
    } else if (relmax == 0) {
        relmax = 1;
    }

    while(loop) {
        loop = 0;
        memset(chars,' ',len);
        for (j = 0; j < len; j++) {
            struct sample *s = &seq->samples[j+offset];
            double relval = s->value - seq->min;
            int step;

            if (opt_log) relval = log(relval+1);
            step = (int) (relval*steps)/relmax;
            if (step < 0) step = 0;
            if (step >= steps) step = steps-1;

            if (row < rows) {
                /* Print the character needed to create the sparkline */
                int charidx = step-((rows-row-1)*charset_len);
                loop = 1;
                if (charidx >= 0 && charidx < charset_len) {
                    chars[j] = opt_fill ? charset_fill[charidx] :
                                          charset[charidx];
                } else if(opt_fill && charidx >= charset_len) {
                    chars[j] = '|';
                }
            } else {
                /* Labels spacing */
                if (seq->labels && row-rows < label_margin_top) {
                    loop = 1;
                    break;
                }
                /* Print the label if needed. */
                if (s->label) {
                    int label_len = strlen(s->label);
                    int label_char = row - rows - label_margin_top;

                    if (label_len > label_char) {
                        loop = 1;
                        chars[j] = s->label[label_char];
                    }
                }
            }
        }
        if (loop) {
            row++;
            output = sdscatlen(output,chars,len);
            output = sdscatlen(output,"\n",1);
        }
    }
    zfree(chars);
    return output;
}