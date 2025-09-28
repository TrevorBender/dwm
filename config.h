#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const Gap default_gap = {.isgap = 0, .realgap = 10, .gappx = 10};
static const unsigned int snap = 32; /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
/* See: <https://www.freedesktop.org/software/fontconfig/fontconfig-user.html>
 */
/* Note: first font is for text, second font is fallback for nerd icons */
static const char *fonts[] = {"Fira Code:size=9",
                              "FiraCode Nerd Font:size=12:weight=bold"};
static const char dmenufont[] = "FiraCode Nerd Font:size=9";

#ifdef COLOR_GRUVBOX
/* Gruvbox color pallete */
/* https://github.com/morhetz/gruvbox?tab=readme-ov-file */
static const char col_bg0[] = "#282828";
static const char col_bg1[] = "#3c3836";
static const char col_bg2[] = "#504945";
static const char col_fg[] = "#ebdbb2";
static const char col_gray[] = "#928374";
static const char col_blue[] = "#458588";
static const char col_red[] = "#cc241d";
static const char col_yellow[] = "#d79921";
static const char col_green[] = "#98971a";
static const char col_purp[] = "#b16286";
static const char col_aqua[] = "#689d6a";
static const char col_orange[] = "#d65d0e";
#endif

#ifdef COLOR_KANAGAWA
/* Kanagawa color pallete */
/* https://github.com/rebelot/kanagawa.nvim/tree/master?tab=readme-ov-file#color-palette
 */
static const char col_bg0[] = "#1f1f28";
static const char col_bg1[] = "#2a2a37";
static const char col_bg2[] = "#363646";
static const char col_fg[] = "#dcd7ba";
static const char col_gray[] = "#727169";
static const char col_blue[] = "#7e9cd8";
static const char col_red[] = "#e82424";
static const char col_yellow[] = "#ff9e3b";
static const char col_green[] = "#98bb6c";
static const char col_purp[] = "#957fb8";
static const char col_aqua[] = "#6a9589";
static const char col_orange[] = "#ffa066";
#endif

#ifdef COLOR_KANAGAWA_LOTUS
/* Kanagawa color pallete */
/* https://github.com/rebelot/kanagawa.nvim/tree/master?tab=readme-ov-file#color-palette
 */
static const char col_bg0[] = "#f2ecbc";
static const char col_bg1[] = "#2a2a37";
static const char col_bg2[] = "#363646";
static const char col_bg0_h[] = "#363646";
static const char col_fg[] = "#545464";
static const char col_gray[] = "#727169";
static const char col_blue[] = "#7e9cd8";
static const char col_red[] = "#e82424";
static const char col_yellow[] = "#ff9e3b";
static const char col_green[] = "#98bb6c";
static const char col_purp[] = "#957fb8";
static const char col_aqua[] = "#6a9589";
static const char col_orange[] = "#ffa066";
#endif

#ifdef COLOR_SOLARIZED_LIGHT
/* Solarized color pallete */
/* https://ethanschoonover.com/solarized/ */
static const char col_bg0[] = "#fdf6e3";  // base3
static const char col_bg1[] = "#eee8d5";  // base2
static const char col_bg2[] = "#93a1a1";  // base1
static const char col_fg[] = "#657b83";   // base00
static const char col_gray[] = "#93a1a1"; // base1
static const char col_blue[] = "#268bd2";
static const char col_red[] = "#dc322f";
static const char col_yellow[] = "#b58900";
static const char col_green[] = "#859900";
static const char col_purp[] = "#6c71c4";
static const char col_aqua[] = "#2aa198";
static const char col_orange[] = "#cb4b16";
#endif

static const char *colors[][3] = {
    /*                  fg          bg         border     */
    [SchemeNorm] = {col_gray, col_bg0, col_bg0},
    [SchemeSel] = {col_blue, col_bg0, col_yellow},
    [SchemeTag] = {col_gray, col_bg0, col_bg0},
    [SchemeTag1] = {col_blue, col_bg1, col_bg0},   /* term */
    [SchemeTag2] = {col_red, col_bg1, col_bg0},    /* firefox */
    [SchemeTag3] = {col_fg, col_bg1, col_bg0},     /* steam */
    [SchemeTag4] = {col_green, col_bg1, col_bg0},  /* movie */
    [SchemeTag5] = {col_yellow, col_bg1, col_bg0}, /* volume */
    [SchemeLayout] = {col_orange, col_bg0, col_bg0},
    [SchemeAudio] = {col_yellow, col_bg0, col_bg0},
    [SchemeBattery] = {col_blue, col_bg0, col_bg0},
    [SchemeMemory] = {col_purp, col_bg0, col_bg0},
    [SchemeCPU] = {col_aqua, col_bg0, col_bg0},
    [SchemeDate] = {col_fg, col_bg0, col_bg0},
};

/* tagging */
static const char *tags[] = {"", "", "", "󰿎", "󰕾"};
static const unsigned int tag_schemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5,
};

/* xprop(1):
 *  WM_CLASS(STRING) = instance, class
 *  WM_NAME(STRING) = title
 */
static const Rule rules[] = {
    /* class            instance        title       tags mask       isfloating
       monitor */
    {"Gimp", NULL, NULL, 0, True, -1},
    {"Lxappearance", NULL, NULL, 0, True, -1},
    {"Lxrandr", NULL, NULL, 0, True, -1},
    {"firefox", NULL, NULL, 1 << 1, False, -1},
    {"steam", NULL, NULL, 1 << 2, False, -1},
    {"Pavucontrol", NULL, NULL, 1 << 4, False, -1},
};

/* layout(s) */
static const float mfact = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;   /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"", tile}, /* first entry is default */
    {"", NULL}, /* no layout function means floating behavior */
    {"", monocle}, {"T", bstack}, {"", bstackhoriz},
};

static const char *monocle_symbols[] = {"󱅊", "󱅋", "󱅌",
                                        "󱅍", "󱅎", "󱅏"};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, toggleview, {.ui = 1 << TAG}},                                 \
      {MODKEY | ControlMask, KEY, view, {.ui = 1 << TAG}},                     \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",     dmenumon, "-fn",   dmenufont, "-nb",    col_bg0,
    "-nf",       col_gray, "-sb",    col_bg0, "-sf",     col_blue, NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *drun[] = {"rofi", "-show", "drun", NULL};
static const char *close_not[] = {"dunstctl", "close-all", NULL};
static const char *backlight_down[] = {"light", "-U", "5", NULL};
static const char *backlight_up[] = {"light", "-A", "5", NULL};
static const char *lock[] = {"i3lock", "-c", col_bg0, NULL};
static const char *SLEEP[] = {"sudo", "pm-suspend", NULL};
static const char *sound_toggle[] = {"amixer", "set", "Master", "toggle", NULL};
static const char *sound_up[] = {"amixer", "set", "Master", "5%+", NULL};
static const char *sound_down[] = {"amixer", "set", "Master", "5%-", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *dragon[] = {"dragon", "--target", NULL};
static const char *network[] = {"networkmanager_dmenu", "-i", NULL};

static const char *music_dock[] = {"eww", "open", "music", NULL};
static const char *eww_close[] = {"eww", "close-all", NULL};
static const char *music_prev[] = {"playerctl", "previous", NULL};
static const char *music_next[] = {"playerctl", "next", NULL};
static const char *music_play_pause[] = {"playerctl", "play-pause", NULL};

static const char *toggle_trans[] = {"picom-trans", "-t", "-c", NULL};

#include "movestack.c"

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = drun}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {0, XF86XK_AudioMute, spawn, {.v = sound_toggle}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = sound_down}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = sound_up}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = backlight_up}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = backlight_down}},
    {0, XF86XK_AudioPrev, spawn, {.v = music_prev}},
    {0, XF86XK_AudioPlay, spawn, {.v = music_play_pause}},
    {0, XF86XK_AudioNext, spawn, {.v = music_next}},
    {MODKEY | ControlMask, XK_n, spawn, {.v = network}},
    {MODKEY | ShiftMask, XK_m, spawn, {.v = music_dock}},
    {MODKEY | ShiftMask, XK_n, spawn, {.v = eww_close}},
    {MODKEY | ShiftMask, XK_t, spawn, {.v = toggle_trans}},
    {MODKEY, XK_grave, spawn, {.v = close_not}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, movestack, {.i = -1}},
    {MODKEY | ShiftMask, XK_i, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = lock}},
    {MODKEY | ShiftMask | ControlMask, XK_l, spawn, {.v = dragon}},
    {MODKEY, XK_equal, setmfact, {.f = 1.5}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},             // tile
    {MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[1]}}, // floating
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},             // monacle
    {MODKEY, XK_n, setlayout, {.v = &layouts[4]}},             // bstackhoriz
    {MODKEY, XK_b, spawn, {.v = browser}},
    {MODKEY | ShiftMask, XK_b, togglebar, {0}},
    {MODKEY, XK_s, spawn, {.v = SLEEP}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -5}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = +5}},
    {MODKEY | ShiftMask, XK_minus, setgaps, {.i = GAP_RESET}},
    {MODKEY, XK_equal, setgaps, {.i = GAP_TOGGLE}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4){MODKEY | ShiftMask, XK_r, quit, {.i = 0}},
    {MODKEY | ShiftMask, XK_q, quit, {.i = 1}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or
 * ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, toggleview, {0}},
    {ClkTagBar, 0, Button3, view, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

/* vim: set noexpandtab: */
