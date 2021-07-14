/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 8;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro Regular:size=13", "JetBrainsMono Nerd Font:style:regular:pixelsize=15" };
static const char *upvol[]          = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
static const char *downvol[]        = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
static const char dmenufont[]       = "monospace:size=10";
static const char *mutevol[]        = { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
static const char col_gray1[]       = "#24283b";
static const char col_gray2[]       = "#1f2335";
static const char col_gray3[]       = "#c0caf5";
static const char col_white[]	      = "#FFFFFF";
static const char col_black[]	      = "#000000";
static const char col_purple[]      = "#BD93F9";
static const char col_green[]       = "#50FA7B";
static const char col_yellow[]	    = "#F1FA8C";
static const char col_magenta[]     = "#FF79C6";
static const char col_bg_d[]        = "#282A36";
static const char col_bg_c[]        = "#1C1C1C";
static const char col_fg_w[]        = "#F8F8F2";
static const char col_fg_y[]        = "#F9CE74";
static const char col_fg_o[]        = "#EA7217";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#8BE9FD";
static const char col_info_blue[]   = "#4fc1ff";
static const char col_bg_alt[]      = "#292e42";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_w, col_bg_c,     col_bg_c },
	[SchemeSel]  = { col_bg_c, col_fg_y,     col_bg_c  },
	[SchemeStatus]  = { col_gray4, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}

	[SchemeTagsSel]  = { col_info_blue, col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}

  [SchemeInfoSel]  = { col_gray3, col_bg_alt,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
/* static const unsigned int baralpha = 0xcc; */
/* static const unsigned int borderalpha = OPAQUE; */
/* static const unsigned int alphas[][3]      = { */
/*               fg      bg        border     */ 
/* 	[SchemeNorm] = { OPAQUE, baralpha, borderalpha }, */
/* 	[SchemeSel]  = { OPAQUE, baralpha, borderalpha }, */
/* }; */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       2 << 9,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "./patches/vanitygaps.c"

/* #include "./patches/fibonacci.c" */
static const Layout layouts[] = {
	/* symbol     arrange function */
  { "",      tile },    /* first entry is default */
	{ "",      monocle },
	{ "",      NULL },    /* no layout function means floating behavior */
  { "[\\]",     dwindle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
  /* { "H[]",      deck },*/
	/* { "TTT",      bstack }, */
 	/* { "[@]",      spiral }, */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "kitty", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg_c, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray1, NULL };
static const char *brbrowser[]  = { "brave-browser", NULL };
static const char *monitor[]    = { "kitty", "gotop", NULL };
static const char *file[]       = { "kitty", "ranger", NULL };
static const char *rofi[]       = { "rofi", "-modi", "run,drun,window", "-show", "drun", NULL};
static const char *emojy[]      = {"splatmoji", "copy", NULL};

#include <X11/XF86keysym.h>
#include "./patches/shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                 XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,			            XK_b,                    spawn,		   SHCMD("feh --bg-fill --randomize ~/.wallpapers/* &") },
	{ MODKEY|ShiftMask,       XK_b,                    togglebar,      {0} },
	{ MODKEY|ShiftMask,       XK_j,                    rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_k,                    rotatestack,    {.i = -1 } },
	{ MODKEY,                 XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                 XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                 XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                 XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,                 XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                 XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,       XK_Return,               zoom,           {0} },
	{ MODKEY,                 XK_q,                    killclient,     {0} },
	{ MODKEY,                 XK_space,                spawn,          {.v = dmenucmd } },
	/* { MODKEY|ShiftMask,    XK_space,                     setlayout,      {0} },  */
	{ MODKEY,			            XK_w,                    spawn,		       {.v = brbrowser} },
	{ MODKEY,			            XK_o,                    spawn,		       {.v = emojy} },
	{ MODKEY,			            XK_r,                    spawn,		       {.v = monitor } },
	{ MODKEY,			            XK_y,                    spawn,		       SHCMD("flameshot gui -p ~/Pictures/screenshots") },
	{ MODKEY|ShiftMask,			  XK_y,                    spawn,		       SHCMD("flameshot full -p ~/Pictures/screenshots") },
	{ MODKEY|ShiftMask,			  XK_v,                    spawn,		       {.v = rofi }},
	{ MODKEY,                 XK_semicolon,            spawn,          SHCMD("skippy-xd") },
	{ MODKEY,                 XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                 XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY,                 XK_n,                    shiftview,      {.i = +1 } },
	{ MODKEY,                 XK_p,                    shiftview,      {.i = -1 } },
	{ MODKEY,                 XK_t,                    setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY|ShiftMask,       XK_t,                    setlayout,      {.v = &layouts[1]} }, // monocle
	{ MODKEY,                 XK_f,                    setlayout,      {.v = &layouts[2]} }, // float
	{ MODKEY|ShiftMask,       XK_f,                    setlayout,      {.v = &layouts[3]} }, // dwindle
	{ MODKEY|ShiftMask,       XK_space,                togglefloating, {0} },
	{ MODKEY,                 XK_c,                    setlayout,      {.v = &layouts[4]} }, // centeredMaster
  { MODKEY|ShiftMask,       XK_c,                    setlayout,      {.v = &layouts[5]} }, // centeredFloatingMaster
	{ MODKEY,                 XK_g,                    togglegaps,     {0} },
	{ MODKEY|ShiftMask,       XK_g,                    defaultgaps,    {0} },
	{ 0,                      XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,                      XF86XK_AudioMute,        spawn,          {.v = mutevol } },
	{ 0,                      XF86XK_AudioRaiseVolume, spawn,          {.v = upvol   } },
	{ MODKEY|ControlMask,		  XK_comma,                cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,     XK_period,               cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,       XK_period,               tagmon,         {.i = +1 } },
  { MODKEY,                 XK_exclam,                focusmon,       {.i = -1 } },
  { MODKEY,                 XK_bar,                focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,       XK_exclam,                tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,       XK_bar,                tagmon,         {.i = +1 } },
	TAGKEYS(                  XK_plus,                      0)
	TAGKEYS(                  XK_bracketleft,                      1)
	TAGKEYS(                  XK_braceleft,                      2)
	TAGKEYS(                  XK_parenleft,                      3)
	TAGKEYS(                  XK_ampersand,                      4)
	TAGKEYS(                  XK_equal,                      5)
	TAGKEYS(                  XK_asterisk,                      6)
	TAGKEYS(                  XK_parenright,                      7)
	TAGKEYS(                  XK_braceright,                      8)
	{ MODKEY|ShiftMask,       XK_q,                    quit,           {0} },
	/* { MODKEY,                 XK_F2,                   spawn,          SHCMD("screenkey -s small --scr 2 -p fixed -g 400x100+2150+1330 --opacity .6 --font-color white") }, */
	/* { MODKEY,                 XK_F3,                   spawn,          SHCMD("killall screenkey") }, */
	/* { MODKEY,              XK_0,                    view,           {.ui = ~0 } }, */
	/* { MODKEY|ShiftMask,    XK_0,                    tag,            {.ui = ~0 } }, */
};

/* bindsym $mod+F12	        exec $term -e nmtui */

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

