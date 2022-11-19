#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	mapa = circle = NULL;
	ray_on = false;
	//sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	// You should do some memory cleaning here, if required
}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	mapa = App->textures->Load("pinball/mapa.png");
	point = App->textures->Load("pinball/point.png");
	bounce = App->textures->Load("pinball/bounce.png");
	palancalefttex = App->textures->Load("pinball/palancaleft.png");
	palancarighttex = App->textures->Load("pinball/palancaright.png");
	stick = App->textures->Load("pinball/stick.png");
	wood=App->textures->Load("pinball/wood.png");

	circle = App->textures->Load("pinball/ball.png"); 
	//box = App->textures->Load("pinball/crate.png");
	//rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	//lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleSceneIntro::OnCollision()
	//lower_ground_sensor->listener = this;

	//Joints
	b2RevoluteJointDef jointdef_palancaleft;
	b2RevoluteJointDef jointdef_palancaright;
	b2RevoluteJoint* joint_palancaleft;
	b2RevoluteJoint* joint_palancaright;

	//Colisiones colliders
	palancaleft = App->physics->CreateRectangle(240, 529, 50, 10, DYNAMIC);
	palancaright = App->physics->CreateRectangle(310, 529, 50, 10, DYNAMIC);
	palancaleft_joint = App->physics->CreateCircle(227, 529, 5, STATIC);
	palancaright_joint = App->physics->CreateCircle(325, 529, 5, STATIC);

	jointdef_palancaleft.Initialize(palancaleft->body, palancaleft_joint->body, palancaleft_joint->body->GetWorldCenter());
	jointdef_palancaright.Initialize(palancaright->body, palancaright_joint->body, palancaright_joint->body->GetWorldCenter());

	jointdef_palancaleft.lowerAngle = -0.2f * b2_pi;
	jointdef_palancaleft.upperAngle = 0.2f * b2_pi;
	jointdef_palancaright.lowerAngle = -0.2f * b2_pi;
	jointdef_palancaright.upperAngle = 0.2f * b2_pi;

	jointdef_palancaleft.enableLimit = true;
	jointdef_palancaright.enableLimit = true;

	joint_palancaleft = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointdef_palancaleft);
	joint_palancaright = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointdef_palancaright);

	//Colliders
	PhysBody* c1 = App->physics->CreateRectangle(SCREEN_WIDTH / 2, 690, SCREEN_WIDTH, 130, STATIC);
	PhysBody* c2 = App->physics->CreateRectangle(71, 350, 10, 700, STATIC);
	PhysBody* c3 = App->physics->CreateRectangle(497, 350, 10, 700, STATIC);
	PhysBody* c4 = App->physics->CreateRectangle(462, 455, 9, 400, STATIC);
	PhysBody* c5 = App->physics->CreateRectangle(96, 450, 9, 300, STATIC);
	PhysBody* c6 = App->physics->CreateRectangle(125, 170, 9, 250, STATIC);
	PhysBody* c7 = App->physics->CreateRectangle(132, 411, 9, 130, STATIC);
	PhysBody* c8 = App->physics->CreateRectangle(422, 411, 9, 130, STATIC);
	PhysBody* c9 = App->physics->CreateRectangle(387, 411, 9, 74, STATIC);
	PhysBody* c10 = App->physics->CreateRectangle(167, 410, 9, 74, STATIC);
	PhysBody* c11 = App->physics->CreateRectangle(420, 207, 9, 55, STATIC);
	PhysBody* c12 = App->physics->CreateRectangle(284, 21, 420, 9, STATIC);
	PhysBody* c13 = App->physics->CreateRectangle(168, 140, 3, 32, STATIC);
	PhysBody* c14 = App->physics->CreateRectangle(202, 140, 3, 32, STATIC);
	PhysBody* c15 = App->physics->CreateRectangle(227, 140, 3, 32, STATIC);
	PhysBody* c16 = App->physics->CreateRectangle(262, 140, 3, 32, STATIC);
	PhysBody* c17 = App->physics->CreateRectangle(290, 140, 3, 32, STATIC);
	PhysBody* c18 = App->physics->CreateRectangle(324, 140, 3, 32, STATIC);
	PhysBody* c19 = App->physics->CreateRectangle(350, 140, 3, 32, STATIC);
	PhysBody* c20 = App->physics->CreateRectangle(385, 140, 3, 32, STATIC);
	PhysBody* c21 = App->physics->CreateRectangle(185, 158, 37, 3, STATIC);
	PhysBody* c22 = App->physics->CreateRectangle(244, 158, 38, 3, STATIC);
	PhysBody* c23 = App->physics->CreateRectangle(307, 158, 37, 3, STATIC);
	PhysBody* c24 = App->physics->CreateRectangle(368, 158, 38, 3, STATIC);
	PhysBody* c25 = App->physics->CreateRectangle(468, 574, 10, 3, STATIC);
	PhysBody* c26 = App->physics->CreateRectangle(490, 574, 10, 3, STATIC);
	PhysBody* c33 = App->physics->CreateRectangle(490, 574, 10, 3, STATIC);

	//points ball
	PhysBody* c27 = App->physics->CreateCircle(185, 128, 12, STATIC);
	PhysBody* c28 = App->physics->CreateCircle(244, 128, 12, STATIC);
	PhysBody* c29 = App->physics->CreateCircle(307, 128, 12, STATIC);
	PhysBody* c30 = App->physics->CreateCircle(368, 128, 12, STATIC);
	PhysBody* c31 = App->physics->CreateCircle(185, 209, 12, STATIC);
	PhysBody* c32 = App->physics->CreateCircle(368, 209, 12, STATIC);

	//bounce

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::Update()
{
	//// If user presses SPACE, enable RayCast
	//if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	// Enable raycast mode
	//	ray_on = !ray_on;

	//	// Origin point of the raycast is be the mouse current position now (will not change)
	//	ray.x = App->input->GetMouseX();
	//	ray.y = App->input->GetMouseY();
	//}

	// If user presses 1, create a new circle object


	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8, DYNAMIC));

		// Add this module (ModuleSceneIntro) as a "listener" interested in collisions with circles.
		// If Box2D detects a collision with this last generated circle, it will automatically callback the function ModulePhysics::BeginContact()
		circles.getLast()->data->listener = this;
	}

	//// If user presses 2, create a new box object
	//if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	//{
	//	boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50,DYNAMIC));
	//}

	//// If user presses 3, create a new RickHead object
	//if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	//{
	//	// Pivot 0, 0
	//	int rick_head[64] = {
	//		14, 36,
	//		42, 40,
	//		40, 0,
	//		75, 30,
	//		88, 4,
	//		94, 39,
	//		111, 36,
	//		104, 58,
	//		107, 62,
	//		117, 67,
	//		109, 73,
	//		110, 85,
	//		106, 91,
	//		109, 99,
	//		103, 104,
	//		100, 115,
	//		106, 121,
	//		103, 125,
	//		98, 126,
	//		95, 137,
	//		83, 147,
	//		67, 147,
	//		53, 140,
	//		46, 132,
	//		34, 136,
	//		38, 126,
	//		23, 123,
	//		30, 114,
	//		10, 102,
	//		29, 90,
	//		0, 75,
	//		30, 62
	//	};

	//	ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	//}

	// Prepare for raycast ------------------------------------------------------
	
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Total distance of the raycast reference segment
	int ray_hit = ray.DistanceTo(mouse);

	// Declare a vector. We will draw the normal to the hit surface (if we hit something)
	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	App->renderer->Blit(mapa, 0, 0);
	App->renderer->Blit(point, 167, 110);
	App->renderer->Blit(point, 227, 110);
	App->renderer->Blit(point, 289, 110);
	App->renderer->Blit(point, 349, 110);
	App->renderer->Blit(point, 349, 190);
	App->renderer->Blit(point, 167, 190);
	App->renderer->Blit(bounce, 177, 390);
	App->renderer->Blit(stick, 475, 600);
	App->renderer->Blit(wood, 0, 624);

	if (palancalefttex != NULL)
	{
		int x, y;
		palancaleft->GetPosition(x, y);
		App->renderer->Blit(palancalefttex, x+7, y-8, NULL, 0.2f, palancaleft->GetRotation()-30);
	}
	if (palancarighttex != NULL)
	{
		int x, y;
		palancaright->GetPosition(x, y);
		App->renderer->Blit(palancarighttex, x+4, y-8, NULL, 0.2f, palancaright->GetRotation()+30);
	}
	/*App->renderer->Blit(palancalefttex, 220, 523);
	App->renderer->Blit(palancarighttex, 290, 523);*/

	// Circles
	p2List_item<PhysBody*>* c = circles.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// If mouse is over this circle, paint the circle's texture
		
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());

		
		c = c->next;
	}

	//// Boxes
	//c = boxes.getFirst();
	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);

	//	// Always paint boxes texture
	//	App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());

	//	// Are we hitting this box with the raycast?
	//	if(ray_on)
	//	{
	//		// Test raycast over the box, return fraction and normal vector
	//		int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
	//		if(hit >= 0)
	//			ray_hit = hit;
	//	}
	//	c = c->next;
	//}

	//// Rick Heads
	//c = ricks.getFirst();
	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);
	//	App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
	//	c = c->next;
	//}

	// Raycasts -----------------
	if(ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	App->audio->PlayFx(bonus_fx);

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}
