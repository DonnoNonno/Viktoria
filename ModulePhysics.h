#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#include "Timer.h"
#include "PerfTimer.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


enum class ColliderType {
	BALL,
	BOUNCE,
	POINTS,
	LOSE,
	NORMAL
	// ..
};
// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody();
	~PhysBody();

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	ColliderType ctype;
	
};

enum bodyType {
	DYNAMIC,
	STATIC,
	KINEMATIC
};




// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	
	// Constructors & Destructors
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	// Main module steps
	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// Create main ground
	void CreateScenarioGround();

	// Create basic physics objects
	PhysBody* CreateCircle(int x, int y, int radius, bodyType type);
	PhysBody* CreateCircleBounce(int x, int y, int radius, bodyType type);
	PhysBody* CreateRectangle(int x, int y, int width, int height, bodyType type);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateChainBumper(int x, int y, int* points, int size);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	// Box2D World
	b2World* world;

	float dt;
	uint frames;

private:

	//FPS
	Timer timer;
	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	float secondsSinceStartup = 0.0f;

	float maxFrameDuration = 0;

	// Debug mode
	bool debug;

	// Main ground
	b2Body* ground;

	// Mouse joint
	b2MouseJoint* mouse_joint;
	b2Body* mouse_body;
};