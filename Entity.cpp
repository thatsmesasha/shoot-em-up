/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 11:25:30 by sasha             #+#    #+#             */
/*   Updated: 2017/08/21 11:25:32 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.hpp"

const int	Entity::ENEMY = 0;
const int	Entity::PLAYER = 1;
const int	Entity::OBSTACLE = 2;
const int	Entity::BULLET = 3;


Entity::Entity(void): type(2) {}

Entity::Entity(int x, int y, int hp, int speed, int type)
: type(type), _x(x), _y(y), _prev_x(x), _prev_y(y), _speed(speed), _hp(hp) {
	// std::cout << "entity created." << std::endl;
}

Entity::Entity(Entity const & entity): type(entity.type) {
	*this = entity;
	// std::cout << "entity copied." << std::endl;
}

Entity::~Entity(void) {
	// std::cout << "entity destroyed." << std::endl;
}

Entity& Entity::operator=(Entity const & entity) {
	this->_x = entity.getX();
	this->_y = entity.getY();
	this->_prev_x = entity.getPrevX();
	this->_prev_y = entity.getPrevY();
	this->_hp = entity.getHP();
	return *this;
}

void	Entity::collide( void )
{
	--this->_hp;
}

int		Entity::getX( void ) const { return this->_x; }
int		Entity::getY( void ) const { return this->_y; }
int		Entity::getPrevX( void ) const { return this->_prev_x; }
int		Entity::getPrevY( void ) const { return this->_prev_y; }
int		Entity::getSpeed( void ) const { return this->_speed; }
int		Entity::getHP( void ) const { return this->_hp; }

void	Entity::setX( int set ) { this->_x = set; }
void	Entity::setY( int set ) { this->_y = set; }
void	Entity::setPrevX( int set ) { this->_prev_x = set; }
void	Entity::setPrevY( int set ) { this->_prev_y = set; }
void	Entity::setSpeed( int set ) { this->_speed = set; }
void	Entity::setHP( int set ) { this->_hp = set; }

void	Entity::incrX() { ++this->_x; }
void	Entity::incrY() { ++this->_y; }
void	Entity::decrX() { --this->_x; }
void	Entity::decrY() { --this->_y; }
void	Entity::decrY( int speed) { this->_y -= speed; }
void	Entity::decrHP() { --this->_hp; }
