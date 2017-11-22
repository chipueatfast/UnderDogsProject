#pragma once
#include "GameObject.h";
class GameObjectMove :public GameObject
{
private:
	GameObject* _weaponObj;

public:
	GameObject* weapon_obj() const
	{
		return _weaponObj;
	}

	void set_weapon_obj(GameObject* game_object)
	{
		_weaponObj = game_object;
	}

protected:
	int _health;
	bool _isThrowing;
public:
	bool is_throwing() const
	{
		return _isThrowing;
	}

	void set_is_throwing(bool is_throwing)
	{
		_isThrowing = is_throwing;
	}

protected:
	float _isImmune;
	string _mainState, _subState, _handState;
public:
	string hand_state() const
	{
		return _handState;
	}

	void set_hand_state(const string& cs)
	{
		_handState = cs;
	}

	string main_state() const
	{
		return _mainState;
	}

	void set_main_state(const string& cs)
	{
		_mainState = cs;
	}

	string sub_state() const
	{
		return _subState;
	}

	void set_sub_state(const string& cs)
	{
		_subState = cs;
	}
protected:
	RECT* _sword;

public:
	virtual void GraphicUpdate(float t) override;
	virtual void PhysicUpdate(float t);
	RECT* sword() const
	{
		return _sword;
	}

	void set_sword(RECT* tag_rect)
	{
		_sword = tag_rect;
	}
	void CalSword();
	void DelSword();
public:
	float is_immune() const
	{
		return _isImmune;
	}
	void set_is_immune(float is_immune)
	{
		_isImmune = is_immune;
	}
	GameObjectMove();
	~GameObjectMove();
	int health() ;
	void set_health(int newHealth);
};

