/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 11:26:49 by sasha             #+#    #+#             */
/*   Updated: 2017/08/21 11:26:49 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP
# define UP 259
# define DOWN 258
# define LEFT 260
# define RIGHT 261
# define ESC 27
# define SPACE 32
# include <iostream>
# include <ncurses.h>
# include <time.h>
# include "Entity.hpp"
# include "Map.hpp"

class Game {
public:
	~Game(void);
	Game(void);

	Game& operator=(Game const &);
	void start(void);
	void end(void);
	bool drawHeader(void);
	bool getInput(void);

	int	getHeight() const;
	int	getWidth() const;

private:
	Game(Game const &);

	int _height;
	int _width;
	time_t _start_time;
	Map *_map;
};

#endif
