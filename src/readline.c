#include "shell.h"
#include "stdio.h"

static void plreadln_flush(void) {}

static int plreadln_putch(int ch) {
    putc(ch);
    return 0;
}

static int plreadln_getch(void) {
    char ch = 0;

    /* temporary alternative to handle unsupported keys */
    ch = getchar();

    if (ch == 0x0d) { return PL_READLINE_KEY_ENTER; }
    if (ch == 0x7f) { return PL_READLINE_KEY_BACKSPACE; }
    if (ch == 0x9) { return PL_READLINE_KEY_TAB; }

    if (ch == 0x1b) {
        ch = plreadln_getch();
        if (ch == '[') {
            ch = plreadln_getch();
            switch (ch) {
            case 'A': return PL_READLINE_KEY_UP;
            case 'B': return PL_READLINE_KEY_DOWN;
            case 'C': return PL_READLINE_KEY_RIGHT;
            case 'D': return PL_READLINE_KEY_LEFT;
            case 'H': return PL_READLINE_KEY_HOME;
            case 'F': return PL_READLINE_KEY_END;
            case '5':
                if (plreadln_getch() == '~') return PL_READLINE_KEY_PAGE_UP;
                break;
            case '6':
                if (plreadln_getch() == '~') return PL_READLINE_KEY_PAGE_DOWN;
                break;
            default: return -1;
            }
        }
    }
    return ch;
}

static void handle_tab(char *buf, pl_readline_words_t words) {
    for (int i = 0; i < builtin_cmd_num; ++i) {
        pl_readline_word_maker_add((char *)builtin_cmds[i].name, words, i == 0, 1, ' ');
    }
}

pl_readline_t setup_readline() {
    pl_readline_t pl = pl_readline_init(plreadln_getch, plreadln_putch, plreadln_flush, handle_tab);
    return pl;
}