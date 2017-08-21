/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 11:28:07 by sasha             #+#    #+#             */
/*   Updated: 2017/08/21 11:28:16 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <iostream>
#include <ncurses.h>

bool	Map::notGameOver( void ) {
	if (this->player->getHP() != 0) return true;
	return false;
}

void	Map::createEntities( void )
{
	int row;
	int column;
	Entity	*entity;

	for (int number = 0; number < 30; number++)
	{
		row = rand() % BUFFER_HEIGHT;
		column = rand() % this->_width;
		if (this->_map[row][column] == NULL)
		{
			entity = new Entity(column, row, 1, 1, Entity::ENEMY);
			this->addEntity(entity);
		}
	}

	for (int i = rand() % 10; i + 20 < this->_width; i += 10 + (rand() % 10))
		for(int j = 0; j < 50; ++j) {
			row = rand() % 3;
			column = i + rand() % 5;
			if (this->_map[row][column] == NULL)
			{
				entity = new Entity(column, row, 1, 1, Entity::OBSTACLE);
				this->addEntity(entity);
			}
	}

	for (int number = 0; number < 20; number++)
	{
		row = rand() % BUFFER_HEIGHT;
		column = rand() % this->_width;
		if (this->_map[row][column] == NULL)
		{
			entity = new Entity(column, row, 1, 1, Entity::OBSTACLE);
			this->addEntity(entity);
		}
	}


}

Map::Map( void ) : _height(0), _width(0) { }
Map::Map( int height, int width ):
	_frames(0),
	_height(height + BUFFER_HEIGHT),
	_width(width),
	_score(0)
{
	this->_map = new Entity**[this->_height];
	for (int i = 0; i < this->_height; ++i) {
		this->_map[i] = new Entity*[this->_width];
	}
	// memset?
	for (int h = 0; h < this->_height; h++)
		for (int w = 0; w < this->_width; w++)
			this->_map[h][w] = NULL;
	this->player = new Entity(width / 2, height / 10 * 9, 3, 0, Entity::PLAYER);
	this->addEntity(this->player);
}

Map::Map( Map const &map ) : _height(0), _width(0) { *this = map; }
Map & Map::operator=( Map const &map ) {
	(void)map;
	return *this;
}

Map::~Map( void )
{
	for (int row = 0; row < this->_height; row++)
		for (int column = 0; column < this->_width; column++)
		{
			if (this->_map[row][column])
				delete this->_map[row][column];
		}
	delete this->_map;
}

Entity	*Map::getEntity( int row, int column )
{
	if (row >= 0 && row < this->_height && column >= 0 && column < this->_width)
		return this->_map[row][column];
	return NULL;
}

void	Map::addEntity( Entity *entity )
{
	if (!entity || entity->getY() >= this->_height - BUFFER_HEIGHT || entity->getY() < 0 || entity->getX() >= this->_width || entity->getX() < 0 )
		return;
	int	row = entity->getY();
	int	column = entity->getX();
	if (this->_map[row][column])
		this->collide(entity, this->_map[row][column]);
	else
		this->_map[row][column] = entity;
}

void	Map::moveEntity( Entity * entity, int hor_speed, int ver_speed )
{
	int row = entity->getY();
	int column = entity->getX();
	this->_map[row][column] = NULL;
	row += ver_speed;
	column += hor_speed;
	if (row == this->_height || row == -1)
		delete entity;
	else if (this->_map[row][column])
		this->collide(entity, this->_map[row][column]);
	else
	{
		this->_map[row][column] = entity;
		entity->setX(column);
		entity->setY(row);
	}
}

void	Map::deleteEntity( Entity *entity )
{
	this->_map[entity->getY()][entity->getX()] = NULL;
	if (entity->type != Entity::PLAYER)
		delete entity;
}

void	Map::collide( Entity* first, Entity* second )
{
	int row = second->getY();
	int column = second->getX();

	if ((first->type == Entity::PLAYER && second->type != Entity::BULLET) ||
		(first->type != Entity::BULLET && second->type == Entity::PLAYER))
	{
		first->setHP(0);
		second->setHP(0);
	}
	else
	{
		first->decrHP();
		second->decrHP();
	}
	if ((first->type == Entity::BULLET && first->getSpeed() < 0) ||
		(second->type == Entity::BULLET && second->getSpeed() < 0))
		this->_score += 50;
	if (second->getHP() == 0)
		this->deleteEntity(second);
	if (first->getHP() == 0)
		this->deleteEntity(first);
	else if (first->getHP() > 0)
	{
		this->_map[row][column] = first;
		first->setX(column);
		first->setY(row);
	}
}

void Map::enemyMissile(Entity* enemy) {
	int i = rand() % 1000;
	if (i % 10 == 0) {
		Entity *missile = new Entity(enemy->getX(), enemy->getY() + 1, 1, 1, Entity::BULLET);
		this->addEntity(missile);
	}
}

void	Map::update( void )
{
	Entity	*entity;

	for (int row = this->_height - 1; row >= 0; row--)
		for (int column = 0; column < this->_width; column++)
		{
			entity = this->_map[row][column];
			if (entity)
			{
				if (entity->type == Entity::ENEMY && this->_frames % FRAMES_ENEMY == 0)
				{
					this->moveEntity(entity, 0, entity->getSpeed());
					this->enemyMissile(entity);
				}
				else if (entity->type == Entity::OBSTACLE && this->_frames % FRAMES_OBSTACLE == 0)
					this->moveEntity(entity, 0, entity->getSpeed());
				else if (entity->type == Entity::BULLET && entity->getSpeed() > 0)
					this->moveEntity(entity, 0, entity->getSpeed());
			}
		}

	for (int row = 0; row < this->_height; row++)
		for (int column = 0; column < this->_width; column++)
		{
			entity = this->_map[row][column];
			if (entity)
			{
				if (entity->type == Entity::BULLET && entity->getSpeed() < 0)
					this->moveEntity(entity, 0, entity->getSpeed());
			}
		}

	if (this->_frames % 100 == 0)
		this->createEntities();
	(this->_frames)++;
	if (this->_frames % 10 == 0)
		++this->_score;
}

int		Map::getFrames( void ) { return this->_frames; }
int		Map::getScore( void ) { return this->_score; }

void	Map::render( void )
{
	Entity *entity;
	mvprintw(1, 0, "%*c", this->_width, ' ');
	for (int row = BUFFER_HEIGHT; row < this->_height; row++)
	{
		mvprintw(row - BUFFER_HEIGHT + 1, 0, "%*c", this->_width, ' ');
		for (int column = 0; column < this->_width; column++)
			if ((entity = this->_map[row][column]))
			{
				attron(COLOR_PAIR(4));
				if (entity->type == Entity::PLAYER)
				{
					mvprintw(entity->getY() + 1 - BUFFER_HEIGHT, entity->getX(), "%c", 'A');
				}
				if (entity->type == Entity::BULLET)
				{
					attron(COLOR_PAIR(2));
					mvprintw(entity->getY() + 1 - BUFFER_HEIGHT, entity->getX(), "%c", '|');
				}
				if (entity->type == Entity::ENEMY)
				{
					attron(COLOR_PAIR(1));
					mvprintw(entity->getY() + 1 - BUFFER_HEIGHT, entity->getX(), "%c", 'w');
				}
				if (entity->type == Entity::OBSTACLE)
				{
					attron(COLOR_PAIR(3));
					mvprintw(entity->getY() + 1 - BUFFER_HEIGHT, entity->getX(), "%c", '@');
				}
			}
	}
}
