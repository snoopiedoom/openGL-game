#pragma once

class Entity
{
private:

protected:
	float x, y;
public:
	Entity();
	~Entity();
};

class Player : public Entity
{
private:
	int fieldOfView;
public:
	Player();
	~Player();
};

class Thrash : public Entity
{
private:
	int velocity;
	float speed;
public:
	Thrash();
	~Thrash();
};

class Enemy : public Entity
{
private:
	bool isThrash;
	float speed;
public:
	Enemy();
	~Enemy();
};

class Ally : public Entity
{
private:
public:
	Ally();
	~Ally();
};