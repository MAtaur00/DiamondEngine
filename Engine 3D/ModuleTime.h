#pragma once
#include "Module.h"
#include "Timer.h"

enum class GameState {
	EDITOR = 0,
	PLAYING,
	PAUSE
};

static class Time : public Module
{
public:
	Time(Application* app, bool start_enabled);
	~Time();

	update_status PreUpdate();

	bool Start();



public:

	float dt = 0.0f;

	Timer timer;
};