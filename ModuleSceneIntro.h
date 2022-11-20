#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:

	// Constructors & Destructors
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void Coll_Map(); //Funcion para generar colisiones diagonals y curvas
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	p2List<PhysBody*> botibotis;
	p2List<PhysBody*> chains;

	// Lists of physics objects
	p2List<PhysBody*> circles;
	PhysBody* palancaleft;
	PhysBody* palancaright;
	PhysBody* palancaleft_joint;
	PhysBody* palancaright_joint;
	PhysBody* bolita;
	// Lower ground sensor (will kill all objects passig through it)
	/*PhysBody* lower_ground_sensor;
	bool sensed;*/

	// Textures
	SDL_Texture* air;
	SDL_Texture* ventilador;
	SDL_Texture* palancarighttex;
	SDL_Texture* palancalefttex;
	SDL_Texture* bounce;
	SDL_Texture* point;
	SDL_Texture* mapa;
	SDL_Texture* wood;
	//SDL_Texture* box;
	//SDL_Texture* rick;

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
