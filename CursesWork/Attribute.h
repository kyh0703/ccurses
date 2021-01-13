
struct Border
{
    Border()
    {
        ls = ACS_VLINE;
        rs = ACS_VLINE;
        ts = ACS_HLINE;
        bs = ACS_HLINE;
        tl = ACS_ULCORNER;
        tr = ACS_URCORNER;
        bl = ACS_LLCORNER;
        br = ACS_LRCORNER;
    }

    chtype ls, rs, ts, bs;
    chtype tl, tr, bl, br;
};

struct Color
{
    Color()
    {
        this->bg = COLOR_BLACK;
        this->fg = COLOR_WHITE;
    }

    Color(int bg, int fg)
    {
        this->bg = bg;
        this->fg = fg;
    }

    int bg, fg;
};

struct Style
{
    Style()
    {
        bg = COLOR_BLACK;
        fg = COLOR_WHITE;
        opt = A_NORMAL;
    }

    Style(int bg, int fg)
    {
        this->bg = bg;
        this->fg = fg;
        this->opt = A_NORMAL;
    }

    Style(int bg, int fg, int opt)
    {
        this->bg = bg;
        this->fg = fg;
        this->opt = opt;
    }

    int bg, fg, opt;
};

struct Rect
{
    Rect()
    {
        h = 0;
        w = 0;
        x = 0;
        y = 0;
    }

    Rect(int h, int w, int x, int y)
    {
        this->h = h;
        this->w = w;
        this->x = x;
        this->y = y;
    }

    int h, w, x, y;
};

struct Pos
{
    Pos(int y, int x)
    {
        this->y = y;
        this->x = x;
    }

    bool operator<(const Pos &rhs) const
    {
        if (y != rhs.y)
            return y < rhs.y;
        return x < rhs.x;
    }

    int y, x;
};

struct Rune
{
    Rune()
    {
        this->c = ' ';
    }

    Rune(chtype c)
    {
        this->s.bg = COLOR_BLACK;
        this->s.fg = COLOR_WHITE;
        this->s.opt = A_NORMAL;
        this->c = c;
    }

    Rune(int bg, int fg, chtype c)
    {
        this->s.bg = bg;
        this->s.fg = fg;
        this->s.opt = A_NORMAL;
        this->c = c;
    }

    Rune(Style s, chtype c)
    {
        this->s = s;
        this->c = c;
    }

    Style s;
    chtype c;
};