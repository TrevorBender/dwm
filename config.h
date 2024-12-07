#include <X11/Xlib.h>
#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

#ifdef SOLARIZED
#define NUMCOLORS 2
static const char colors[NUMCOLORS][ColLast][8] = {
    // border    foreground background
    { "#fdf6e3", "#657b83", "#fdf6e3" }, // 1 = normal
    //{ "#6c71c4", "#fdf6e3", "#657b83" }, // 2 = selected
    { "#00ff00", "#fdf6e3", "#657b83" }, // 2 = selected
};
#endif

#ifdef GRUVBOX
#define NUMCOLORS 17
static const char colors[NUMCOLORS][ColLast][17] = {
    /* border    fg         bg */
    { "#282828", "#928374", "#282828"  },        /* [0]  01 - Client normal */
    { "#ebdbb2", "#458588", "#282828"  },        /* [1]  02 - Client selected */
    { "#83a598", "#fb4934", "#282828"  },        // [2]  03 - Client urgent
    { "#83a598", "#83a598", "#282828"  },        // [3]  04 - Client occupied
    { "#282828", "#fb4934", "#282828"  },        // [4]  05 - Red
    { "#282828", "#fabd2f", "#282828"  },        // [5]  06 - Yellow
    { "#282828", "#b8bb26", "#282828"  },        // [6]  07 - Green
    { "#282828", "#928374", "#282828"  },        // [7]  08 - Dark grey
    { "#282828", "#d5c4a1", "#282828"  },        // [8]  09 - Light grey
    { "#928374", "#928374", "#282828"  },        // [9]  0A - Bar normal
    { "#3c3836", "#a89985", "#282828"  },        // [10] 0B - Bar selected
    { "#fb4934", "#fb4934", "#282828"  },        // [11] 0C - Bar urgent
    { "#928374", "#458588", "#282828"  },        // [12] 0D - Bar occupied
    { "#3c3836", "#3c3836", "#282828"  },        // [13] 0E - Tag normal
    { "#83a598", "#83a598", "#282828"  },        // [14] 0F - Tag selected
    { "#fb4934", "#fb4934", "#282828"  },        // [15] 10 - Tag urgent
    { "#3c3836", "#928374", "#282828"  },        // [16] 11 - Tag occupied
};
#endif

//static const char normbordercolor[] = "#fdf6e3";
//static const char normbgcolor[]     = "#fdf6e3";
//static const char normfgcolor[]     = "#657b83";
//static const char selbordercolor[]  = "#6c71c4";
//static const char selbgcolor[]      = "#657b83";
//static const char selfgcolor[]      = "#fdf6e3";

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode Nerd Font:pixelsize=10" };
static const char dmenufont[]       = "FiraCode Nerd Font:pixelsize=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#928374", "#282828", "#282828" },
	[SchemeSel]  = { "#458588", "#282828",  "#ebdbb2"  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* xprop(1):
 *  WM_CLASS(STRING) = instance, class
 *  WM_NAME(STRING) = title
 */
static const Rule rules[] = {
    /* class            instance        title       tags mask       isfloating   iscentered     monitor */
    { "Gimp",           NULL,           NULL,       0,              True,        False,         -1 },
    { "Lxappearance",   NULL,           NULL,       0,              True,        True,          -1 },
    { "Lxrandr",        NULL,           NULL,       0,              True,        True,          -1 },
    { "Firefox",        NULL,           NULL,       1 << 1,         False,       False,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/* #include "bstack.c" */
/* #include "bstackhoriz.c" */
/* #include "gaplessgrid.c" */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};
    /* { "T  ",      bstack  }, */
    /* { "=  ",      bstackhoriz }, */
    /* { "||=",      gaplessgrid }, */
/* }; */

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
/* static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL }; */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

static const char *drun[] = { "rofi", "-show", "drun", NULL };

static const int mouse_coords[] = { (2256/2), 0 }; // middle, top of screen

static const char * backlight_down[] = { "light", "-U", "5", NULL };
static const char * backlight_up[] = { "light", "-A", "5", NULL };
static const char * slock[] = { "slock", NULL };
static const char * SLEEP[] = { "sudo", "pm-suspend", NULL };
static const char * sound_toggle[] = { "amixer", "set", "Master", "toggle", NULL };
static const char * sound_up[] = { "amixer", "set", "Master", "5%+", NULL };
static const char * sound_down[] = { "amixer", "set", "Master", "5%-", NULL };
static const char * browser[] = { "firefox", NULL };
static const char * dragon[] = { "dragon --target", NULL };

/* #include "mousewarp.c" */
/* #include "movestack.c" */
/* #include "focusroot.c" */

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = drun } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { 0,                            XF86XK_AudioMute,    spawn,          {.v = sound_toggle } },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = sound_down } },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = sound_up } },
    { 0,                            XF86XK_MonBrightnessUp, spawn, {.v = backlight_up } },
    { 0,                            XF86XK_MonBrightnessDown, spawn, {.v = backlight_down } },
    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    /* { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } }, */
    /* { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } }, */
    { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    /* { MODKEY|ShiftMask,             XK_h,      focusroot,      {0} }, */
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slock } },
    { MODKEY|ShiftMask|ControlMask, XK_l,      spawn,          {.v = dragon } },
    { MODKEY,                       XK_equal,  setmfact,       {.f = 1.5} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
    { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} }, // floating
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monacle
    /* { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[4]} }, // bstackhoriz */
    /* { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} }, // gaplessgrid */
    { MODKEY,                       XK_b,      spawn,          {.v = browser } },
    { MODKEY,                       XK_s,      spawn,          {.v = SLEEP } },
    /* { MODKEY|ShiftMask,             XK_m,      warpmouse,      {.v = mouse_coords } }, */
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    /* { MODKEY|ShiftMask|ControlMask, XK_p,      togglepassthrough, {0} }, */
    /* TODO: create a custom nvim anywhere */
    /* { MODKEY,                       XK_v,      spawn,          { .v = vim_anywhere } }, */
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

