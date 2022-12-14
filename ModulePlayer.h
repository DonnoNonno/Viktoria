#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Ball things
	PhysBody* ball;
	SDL_Texture* balltex;

	//Ventilador
	SDL_Texture* air;
	SDL_Texture* ventilador;

	//Fx
	uint flipper_fx;

	int countvel;
	float velshot = 1.0f;
	bool soplar;
};