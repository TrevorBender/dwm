/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[] = 
"-*-terminus2-medium-r-*-*-12-*-*-*-*-*-*-*"
//","
//"-*-stlarch-medium-r-*-*-12-*-*-*-*-*-*-*" 
;
//static const char font[] = "-*-droid sans mono-medium-r-normal-*-*-*-*-*-*-*-*-*";

#define NUMCOLORS 2
static const char colors[NUMCOLORS][ColLast][8] = {
    // border    foreground background
    { "#fdf6e3", "#657b83", "#fdf6e3" }, // 1 = normal
    //{ "#6c71c4", "#fdf6e3", "#657b83" }, // 2 = selected
    { "#00ff00", "#fdf6e3", "#657b83" }, // 2 = selected
};

//static const char normbordercolor[] = "#fdf6e3";
//static const char normbgcolor[]     = "#fdf6e3";
//static const char normfgcolor[]     = "#657b83";
//static const char selbordercolor[]  = "#6c71c4";
//static const char selbgcolor[]      = "#657b83";
//static const char selfgcolor[]      = "#fdf6e3";

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
//static const char *tags[] = { "☕", "☯", "☮", "✇", "☊"};
static const char *tags[] = { "Â", "À", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "\uE16A", "\uE16B", "\uE16C", "\uE16D", "\uE16E", "\uE16F", "\uE170", "\uE171", "\uE172" };

static const Rule rules[] = {
    /* class            instance        title       tags mask       isfloating   iscentered     monitor */
    { "Gimp",           NULL,           NULL,       0,              True,        False,         -1 },
    { "Lxappearance",   NULL,           NULL,       0,              True,        True,          -1 },
    { "Lxrandr",        NULL,           NULL,       0,              True,        True,          -1 },
    { "Firefox",        NULL,           NULL,       1 << 1,         False,       False,         -1 },
    { "Pidgin",         "Preferences",  NULL,       0,              True,        True,          -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "É",      tile },    /* first entry is default */
    { "Ê",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "Ì",      bstack  },
    { "Ë",      bstackhoriz },
    { "Í",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} },\
{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} },\
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },\
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
//static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *clear_notification[] = { "cln", NULL };

static const int mouse_coords[] = { (1920/2), 0 }; // middle, top of screen

static const char * kbd_backlight_down[] = { "kbd_backlight", "down", NULL };
static const char * kbd_backlight_up[] = { "kbd_backlight", "up", NULL };
static const char * backlight_down[] = { "backlight", "down", NULL };
static const char * backlight_up[] = { "backlight", "up", NULL };
static const char * slock[] = { "slock", NULL };
static const char * slock_and_sleep[] = { "slocksleep", NULL };
static const char * SLEEP[] = { "SLEEP", NULL };
static const char * sound_toggle[] = { "amixer", "set", "Master", "toggle", NULL };
static const char * sound_up[] = { "amixer", "set", "Master", "5%+", NULL };
static const char * sound_down[] = { "amixer", "set", "Master", "5%-", NULL };
static const char * lxrandr[] = { "lxrandr", NULL };

#include "mousewarp.c"
#include "movestack.c"
#include "focusroot.c"

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY|ShiftMask,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    //{ MODKEY,                       XK_i,      spawn,          {.v = mpc_toggle } },
    //{ MODKEY,                       XK_o,      spawn,          {.v = mpc_next } },
    //{ MODKEY,                       XK_u,      spawn,          {.v = mpc_prev } },
    //{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = mpc_seekf } },
    //{ MODKEY|ShiftMask,             XK_u,      spawn,          {.v = mpc_seekr } },
    { MODKEY,                       XK_F1,     spawn,          {.v = slock_and_sleep } },
    { MODKEY,                       XK_F3,     spawn,          {.v = kbd_backlight_down } },
    { MODKEY,                       XK_F4,     spawn,          {.v = kbd_backlight_up } },
    { MODKEY,                       XK_F5,     spawn,          {.v = backlight_down } },
    { MODKEY,                       XK_F6,     spawn,          {.v = backlight_up } },
    { MODKEY,                       XK_F8,     spawn,          {.v = lxrandr } },
    { MODKEY,                       XK_F10,    spawn,          {.v = sound_toggle } },
    { MODKEY,                       XK_F11,    spawn,          {.v = sound_down } },
    { MODKEY,                       XK_F12,    spawn,          {.v = sound_up } },
    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_h,      focusroot,      {0} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slock } },
    { MODKEY,                       XK_equal,  setmfact,       {.f = 1.5} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_c,      spawn,          {.v = clear_notification } },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
    { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} }, // floating
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monacle
    { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} }, // bstack
    { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[4]} }, // bstackhoriz
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} }, // gaplessgrid
    { MODKEY,                       XK_s,      spawn,          {.v = SLEEP } },
    { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = slock_and_sleep } },
    { MODKEY|ShiftMask,             XK_m,      warpmouse,      {.v = mouse_coords } },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask|ControlMask, XK_p,      togglepassthrough, {0} },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_r,      quit,           {.i = 0} },
    { MODKEY|ShiftMask,             XK_q,      quit,           {.i = 1} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        toggleview,           {0} },
    { ClkTagBar,            0,              Button3,        view,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

