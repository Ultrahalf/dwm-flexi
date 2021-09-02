/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 30;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 0;   /* 0 means derive from font, >= 1 explicit height */
static const int vertpad                 = 10;  /* vertical padding of bar */
static const int sidepad                 = 10;  /* horizontal padding of bar */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */
/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_NONE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static int fakefsindicatortype           = INDICATOR_PLUS_AND_LARGER_SQUARE;
static int floatfakefsindicatortype      = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]          	 = { "SauceCodePro Nerd Font:pixelsize=14", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
static const char dmenufont[]            = "SauceCodePro Nerd Font:pixelsize=14";
static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfloatcolor[]             = "#db8fd9";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#005577";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";



static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};


static const char *layoutmenu_cmd = "layoutmenu.sh";
const char *spcmd1[] = { "alacritty", "--class", "spterm,spterm", "-t", "Spterm", "--config-file", "/home/ultrahalf/.config/alacritty/spterm.yml", NULL };
const char *spcmd2[] = { "alacritty", "--class", "spcalc,spcalc", "-t", "Spcalc", "--config-file", "/home/ultrahalf/.config/alacritty/spterm.yml", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */

static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        = { "", "", "", "", "", "", "", "", "" },
	[ALT_TAGS_DECORATION] = { "", "", "", "", "", "", "", "", "" },
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "firefox", .tags = 1 << 3)
	RULE(.class = "discord", .tags = 1 << 5)
	RULE(.class = "signal", .tags = 1 << 5)
	RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
	RULE(.instance = "spcalc", .tags = SPTAG(1), .isfloating = 1)
};

static const MonitorRule monrules[] = {
	/* monitor  tag   layout  mfact  nmaster  showbar  topbar */
	{  1,       -1,   2,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,      -1,   0,      -1,    -1,      -1,      -1     }, // default
};


/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor  bar    alignment         widthfunc                drawfunc                clickfunc                name */
	{ -1,       0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
	{  0,       0,     BAR_ALIGN_RIGHT,  width_systray,           draw_systray,           click_systray,           "systray" },
	{ -1,       0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
	{ 'A',      0,     BAR_ALIGN_RIGHT,  width_status2d,          draw_status2d,          click_statuscmd,         "status2d" },
	{ -1,       0,     BAR_ALIGN_NONE,   width_wintitle,          draw_wintitle,          click_wintitle,          "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */
/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};


/* key definitions */
#define Super Mod4Mask
#define Alt   Mod1Mask
#define Shift ShiftMask 
#define Ctrl  ControlMask
#define TAGKEYS(KEY,TAG) \
	{ Super,                        KEY,      view,           {.ui = 1 << TAG} }, \
	{ Super|Ctrl,                   KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Super|Shift,                  KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Super|Ctrl|Shift,             KEY,      toggletag,      {.ui = 1 << TAG} },



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	topbar ? NULL : "-b",
	NULL
};
static const char *termcmd[]  = { "alacritty", NULL };

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"
#include <X11/XF86keysym.h>


static Key keys[] = {
	/* modifier                     key            function                argument */
	{ Super,                        XK_Return,      zoom,                   {0} },
	{ Super, 			            XK_space, 	    spawn, 			        {.v = termcmd } },
	{ Super, 			            XK_r, 		    spawn, 			        {.v = dmenucmd } },
	{ Super, 			            XK_n, 		    focusstack, 		    {.i = +1 } },
	{ Super|Shift, 		            XK_n, 		    movestack, 		        {.i = +1 } },
	{ Super, 			            XK_e, 		    focusstack, 		    {.i = -1 } },
	{ Super|Shift, 		            XK_e, 		    movestack, 		        {.i = -1 } },
	{ Super, 			            XK_k, 		    setmfact, 		        {.f = -0.05} },
	{ Super|Shift,     	            XK_k,          	setcfact,               {.f = -0.25} },
	{ Super, 			            XK_h, 		    setmfact, 		        {.f = +0.05} },
	{ Super|Shift,     	            XK_h,          	setcfact,               {.f = +0.25} },
	{ Super, 			            XK_b, 		    togglebar, 		        {0} },
	{ Super,     			        XK_b,          	setcfact,               {0} }, // same binding
	{ Super, 			            XK_u, 		    focusurgent, 		    {0} },
	{ Super,                        XK_o,           winview,                {0} },
	{ Super|Shift,                  XK_f,          	togglefakefullscreen,  	{0} },
	{ Super, 			            XK_equal, 	    incnmaster, 		    {.i = +1 } },
	{ Super, 			            XK_minus, 	    incnmaster, 		    {.i = -1 } },
	{ Super, 			            XK_q, 		    killclient, 		    {0} },
	{ Super|Shift,                  XK_q,           quit,                   {1} },
	{ Super, 			            XK_w,		    spawn, 			        SHCMD("brave") },
	{ Super|Shift, 		            XK_w, 		    spawn, 			        SHCMD("alacritty -e sudo nmtui") },
	{ Super, 			            XK_f, 		    spawn, 			        SHCMD("alacritty -e ranger") },
	{ Super|Shift, 		            XK_p, 		    spawn, 			        SHCMD("passmenu -i") },
	{ Super|Shift, 		            XK_r, 		    spawn, 			        SHCMD("dmenuunicode") },
	{ Super,						XK_BackSpace,	spawn, 			        SHCMD("sysact") },

	/* AUDIO */
	{ Super, 			            XK_p, 		    spawn, 			        SHCMD("mpc toggle ; pauseallmpv") },
	{ Super, 			            XK_m, 		    spawn, 			        SHCMD("alacritty -e ncmpcpp") },
	{ Super|Shift,		            XK_m,		    spawn,			        SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },

	/* MOVEMENT */
	{ Super,                        XK_Tab,         view,                   {0} },
	{ Super, 			            XK_a, 		    shiftviewclients, 	    { .i = -1 } },
	{ Super, 			            XK_t, 		    shiftviewclients, 	    { .i = +1 } },
	{ Alt,                          XK_space,       spawn,                  SHCMD("activatewindow.sh") },

  /* GAPS */
	{ Alt,                          XK_g,          incrgaps,               {.i = +1 } },
	{ Alt|Shift,                    XK_g,          incrgaps,               {.i = -1 } },
	{ Alt,                          XK_t,          togglegaps,             {0} },
	{ Alt,                          XK_b,          togglebarpadding,       {0} },
	{ Alt,                          XK_0,          defaultgaps,            {0} },

  /* LAYOUT */
	{ Alt,                          XK_q,          togglefakefullscreen,   {0} },
	{ Alt,                          XK_w,          setlayout,              {.v = &layouts[0]} },
	{ Alt,                          XK_f,          setlayout,              {.v = &layouts[1]} },
	{ Alt,                          XK_p,          setlayout,              {.v = &layouts[2]} },
	{ Super|Shift,                  XK_space,      togglefloating,         {0} },
	{ Alt,           		        XK_x, 	       cyclelayout,            {.i = +1 } },
	{ Alt,           		        XK_z, 	       cyclelayout,            {.i = -1 } },

	/* SCRATCHPAD */
	{ Super, 			            XK_Return, 	   togglescratch, 		   {.ui = 0} },
	{ Super, 			            XK_slash, 	   togglescratch, 		   {.ui = 1} },
	{ Super, 			            XK_x, 		   togglescratch, 		   {.ui = 2 } },
	{ Super, 			            XK_z, 		   setscratch, 		       {.ui = 2 } },
	{ Super|Shift, 		            XK_z, 		   removescratch, 		   {.ui = 2 } },
	{ Super,                        XK_v,          view,                   {.ui = ~SPTAGMASK } },
	//{ Super|Shift,                  XK_0,          tag,                    {.ui = ~SPTAGMASK } },

	/* MONITOR */
	{ Super,                        XK_comma,      focusmon,               {.i = -1 } },
	{ Super,                        XK_period,     focusmon,               {.i = +1 } },
	{ Super|Shift,                  XK_comma,      tagmon,                 {.i = -1 } },
	{ Super|Shift,                  XK_period,     tagmon,                 {.i = +1 } },

	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)

	/* SPECIALKEYS */
	{ Super, 			            XK_Insert, 	    spawn, 			        SHCMD("xdotool type $(cat ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
	{ 0, 			                XK_Print, 	    spawn, 			        SHCMD("maimpick") },
	{ Super, 	  	                XK_Print, 	    spawn, 			        SHCMD("maim -i $(xdotool getactivewindow) Pictures/scrots/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	//{ Super, 			            XK_Scroll_Lock, spawn, 			        SHCMD("") },

	/* FUNCTION KEYS */
	//{ Super, 			             XK_F1,	 	     spawn, 			    SHCMD("") },
	//{ Super, 			             XK_F2,	 	     spawn, 			    SHCMD("") },
	//{ Super, 			             XK_F3,	 	     spawn, 			    SHCMD("") },
	{ Super, 			             XK_F4,          xrdb,                  {.v = NULL } },

	{ Super, 			             XK_F5,	 	     spawn, 			    SHCMD("alacritty -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ Super, 			             XK_F6,	 	     spawn, 			    SHCMD("dmenurecord") },
	{ Super, 			             XK_F7,	 	     spawn, 			    SHCMD("dmenurecord kill") },
	{ Super, 			             XK_F8,	 	     spawn, 			    SHCMD("killall screenkey || screenkey &") },

	{ Super, 			             XK_F9,	 	     spawn, 			    SHCMD("dmenumount") },
	{ Super, 			             XK_F10, 	     spawn, 			    SHCMD("dmenuumount") },
	{ Super, 			             XK_F11, 	     spawn, 			    SHCMD("displayselect") },
	{ Super, 			             XK_F12, 	     spawn, 			    SHCMD("remaps & notify-send \"keyboard remapped.. \"") },

	/* FN KEYS */
	{ 0, 	           XF86XK_AudioMute,		     spawn, 	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, 	           XF86XK_AudioRaiseVolume,      spawn, 	SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, 	           XF86XK_AudioLowerVolume,      spawn, 	SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, 	           XF86XK_AudioPrev,		     spawn, 	SHCMD("mpc prev") },
	{ 0, 	           XF86XK_AudioNext,		     spawn, 	SHCMD("mpc next") },
	{ 0, 	           XF86XK_AudioPause,		     spawn, 	SHCMD("mpc pause") },
	{ 0, 	           XF86XK_AudioPlay,		     spawn, 	SHCMD("mpc play") },
	{ 0, 	           XF86XK_AudioStop,		     spawn, 	SHCMD("mpc stop") },
	{ 0, 	           XF86XK_AudioRewind,		     spawn, 	SHCMD("mpc seek -10") },
	{ 0, 	           XF86XK_AudioForward,			 spawn, 	SHCMD("mpc seek +10") },
	{ 0, 	           XF86XK_AudioMicMute,	         spawn, 	SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, 	           XF86XK_Launch1,			     spawn, 	SHCMD("xset dpms force off") },
	{ 0, 	           XF86XK_TouchpadToggle,	     spawn, 	SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, 	           XF86XK_TouchpadOff,			 spawn, 	SHCMD("synclient TouchpadOff=1") },
	{ 0, 	           XF86XK_TouchpadOn, 		     spawn, 	SHCMD("synclient TouchpadOff=0") },
	{ 0, 	           XF86XK_MonBrightnessUp,	     spawn, 	SHCMD("xbacklight -inc 5") },
	{ 0, 	           XF86XK_MonBrightnessDown,     spawn, 	SHCMD("xbacklight -dec 5") },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,                   Button4,        sigstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,                   Button5,        sigstatusbar,   {.i = 5 } },
	{ ClkClientWin,         Super,               Button1,        movemouse,      {0} },
	{ ClkClientWin,         Super,               Button2,        togglefloating, {0} },
	{ ClkClientWin,         Super,               Button3,        resizemouse,    {0} },
	{ ClkClientWin,         Super,               Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         Super,               Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         Super,               Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         Super,               Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            Super,               Button1,        tag,            {0} },
	{ ClkTagBar,            Super,               Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum                    function */
	{ "focusstack",              focusstack },
	{ "setmfact",                setmfact },
	{ "togglebar",               togglebar },
	{ "incnmaster",              incnmaster },
	{ "togglefloating",          togglefloating },
	{ "focusmon",                focusmon },
	{ "focusurgent",             focusurgent },
	{ "tagmon",                  tagmon },
	{ "zoom",                    zoom },
	{ "incrgaps",                incrgaps },
	{ "incrigaps",               incrigaps },
	{ "incrogaps",               incrogaps },
	{ "incrihgaps",              incrihgaps },
	{ "incrivgaps",              incrivgaps },
	{ "incrohgaps",              incrohgaps },
	{ "incrovgaps",              incrovgaps },
	{ "togglegaps",              togglegaps },
	{ "defaultgaps",             defaultgaps },
	{ "setgaps",                 setgapsex },
	{ "view",                    view },
	{ "viewall",                 viewallex },
	{ "viewex",                  viewex },
	{ "toggleview",              toggleview },
	{ "shiftview",               shiftview },
	{ "shiftviewclients",        shiftviewclients },
	{ "cyclelayout",             cyclelayout },
	{ "toggleviewex",            toggleviewex },
	{ "tag",                     tag },
	{ "tagall",                  tagallex },
	{ "tagex",                   tagex },
	{ "toggletag",               toggletag },
	{ "toggletagex",             toggletagex },
	{ "togglefakefullscreen",    togglefakefullscreen },
	{ "togglescratch",           togglescratch },
	{ "killclient",              killclient },
	{ "winview",                 winview },
	{ "xrdb",                    xrdb },
	{ "quit",                    quit },
	{ "setlayout",               setlayout },
	{ "setlayoutex",             setlayoutex },
};

