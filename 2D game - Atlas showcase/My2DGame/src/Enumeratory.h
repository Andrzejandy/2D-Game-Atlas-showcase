#pragma once

enum keyboard_keys
{
	w = 119,
	s = 115,
	a = 97,
	b = 98,
	c = 99,
	d = 100,
	q = 113,
	e = 101,
	f = 102,
	g = 103,
	h = 104,
	i = 105,
	j = 106,
	k = 107,
	l = 108,
	m = 109,
	n = 110,
	o = 111,
	p = 112

};

enum enum_way
{
	NORTH = 2,
	SOUTH = 0,
	WEST = 3,
	EAST = 1,
	NE = 4,
	SE = 5,
	SW = 6,
	NW = 7
};

enum CurrentGameStatus
{
	game_running = 0,
	game_menu = 1,
	game_map_select = 2,
	game_paused = 3,
	game_options = 4,
	game_starts = 5,
	game_load = 6
};
