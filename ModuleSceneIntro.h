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

	PhysBody* s1;
	PhysBody* c1;
	PhysBody* c2;
	PhysBody* c3;
	PhysBody* c4;
	PhysBody* c5;
	PhysBody* c6;
	PhysBody* c7;
	PhysBody* c8;
	PhysBody* c9;
	PhysBody* c10;
	PhysBody* c11;
	PhysBody* c12;
	PhysBody* c13;
	PhysBody* c14;
	PhysBody* c15;
	PhysBody* c16;
	PhysBody* c17;
	PhysBody* c18;
	PhysBody* c19;
	PhysBody* c20;
	PhysBody* c21;
	PhysBody* c22;
	PhysBody* c23;
	PhysBody* c24;
	PhysBody* c25;
	PhysBody* c26;
	PhysBody* c27;
	PhysBody* c28;
	PhysBody* c29;
	PhysBody* c30;
	PhysBody* c31;
	PhysBody* c32;
	PhysBody* c33;
	PhysBody* inicio;
	PhysBody* cb1;
	PhysBody* cb2;
	PhysBody* cb3;
	PhysBody* cb4;
	PhysBody* cb5;
	PhysBody* cb6;

	//Scenes
	SDL_Texture* title;
	bool titlescene = true;
	SDL_Texture* losescreen;
	SDL_Texture* winscreen;

	//Textures
	SDL_Texture* palancarighttex;
	SDL_Texture* palancalefttex;
	SDL_Texture* bounce;
	SDL_Texture* point;
	SDL_Texture* mapa;
	SDL_Texture* puntuation;
	SDL_Texture* maderita;
	SDL_Texture* barrapuntos;

	// Music & FX
	uint dead_fx;
	uint point_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;

	// Variables de condición muerte
	bool solouno = false;
	bool muerto = false;
	bool win = false;

	bool sumar = false;

	int puntos = 0;

	int timer = 150;

};
