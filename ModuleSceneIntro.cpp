#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	mapa = NULL;
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

	//Load scenes
	title = App->textures->Load("pinball/titlescreen.png");
	losescreen = App->textures->Load("pinball/losescreen.png");
	winscreen = App->textures->Load("pinball/winscreen.png");

	// Load textures
	mapa = App->textures->Load("pinball/mapa.png");
	puntuation=App->textures->Load("pinball/puntuation.png");
	maderita = App->textures->Load("pinball/maderita.png");
	barrapuntos = App->textures->Load("pinball/barrapuntos.png");
	point = App->textures->Load("pinball/point.png");
	bounce = App->textures->Load("pinball/bounce.png");
	palancalefttex = App->textures->Load("pinball/palancaleft.png");
	palancarighttex = App->textures->Load("pinball/palancaright.png");

	//box = App->textures->Load("pinball/crate.png");
	//rick = App->textures->Load("pinball/rick_head.png");
	//Load sounds
	//music = App->audio->LoadFx("pinball/Audios/music-.ogg");
	dead_fx = App->audio->LoadFx("pinball/Audios/lose_sound.wav");

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	//lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleSceneIntro::OnCollision()
	//lower_ground_sensor->listener = this;

	//Start Ball
	//circles.add(App->physics->CreateCircle(480, 560, 8, DYNAMIC));

	//Plancas Joints
	b2RevoluteJointDef jointdef_palancaleft;
	b2RevoluteJointDef jointdef_palancaright;
	b2RevoluteJoint* joint_palancaleft;
	b2RevoluteJoint* joint_palancaright;

	//Palancas Logic
	palancaleft = App->physics->CreateRectangle(240, 530, 50, 15, DYNAMIC);
	palancaright = App->physics->CreateRectangle(310, 530, 50, 15, DYNAMIC);
	palancaleft_joint = App->physics->CreateCircle(227, 530, 5, STATIC);
	palancaright_joint = App->physics->CreateCircle(325, 530, 5, STATIC);

	jointdef_palancaleft.Initialize(palancaleft->body, palancaleft_joint->body, palancaleft_joint->body->GetWorldCenter());
	jointdef_palancaright.Initialize(palancaright->body, palancaright_joint->body, palancaright_joint->body->GetWorldCenter());

	jointdef_palancaleft.lowerAngle = -0.1f * b2_pi;
	jointdef_palancaleft.upperAngle = 0.1f * b2_pi;
	jointdef_palancaright.lowerAngle = -0.1f * b2_pi;
	jointdef_palancaright.upperAngle = 0.1f * b2_pi;

	jointdef_palancaleft.enableLimit = true;
	jointdef_palancaright.enableLimit = true;

	joint_palancaleft = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointdef_palancaleft);
	joint_palancaright = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointdef_palancaright);

	//Colliders
	s1 = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, 689, SCREEN_WIDTH, 130);
	s1->ctype = ColliderType::LOSE;
	s1->listener = this;
	c1 = App->physics->CreateRectangle(SCREEN_WIDTH / 2, 690, SCREEN_WIDTH, 130, STATIC);
	c2 = App->physics->CreateRectangle(71, 325, 10, 600, STATIC);
	c3 = App->physics->CreateRectangle(497, 325, 10, 600, STATIC);
	c4 = App->physics->CreateRectangle(462, 440, 9, 370, STATIC);
	c5 = App->physics->CreateRectangle(96, 425, 9, 200, STATIC);
	c6 = App->physics->CreateRectangle(125, 195, 9, 200, STATIC);
	c7 = App->physics->CreateRectangle(132, 411, 9, 130, STATIC);
	c8 = App->physics->CreateRectangle(422, 411, 9, 130, STATIC);
	c9 = App->physics->CreateRectangle(387, 411, 9, 74, STATIC);
	c10 = App->physics->CreateRectangle(167, 410, 9, 74, STATIC);
	c11 = App->physics->CreateRectangle(420, 207, 9, 55, STATIC);
	c12 = App->physics->CreateRectangle(284, 21, 420, 9, STATIC);
	c13 = App->physics->CreateRectangle(168, 140, 3, 32, STATIC);
	c14 = App->physics->CreateRectangle(202, 140, 3, 32, STATIC);
	c15 = App->physics->CreateRectangle(227, 140, 3, 32, STATIC);
	c16 = App->physics->CreateRectangle(262, 140, 3, 32, STATIC);
	c17 = App->physics->CreateRectangle(290, 140, 3, 32, STATIC);
	c18 = App->physics->CreateRectangle(324, 140, 3, 32, STATIC);
	c19 = App->physics->CreateRectangle(350, 140, 3, 32, STATIC);
	c20 = App->physics->CreateRectangle(385, 140, 3, 32, STATIC);
	c21 = App->physics->CreateRectangle(185, 158, 37, 3, STATIC);
	c22 = App->physics->CreateRectangle(244, 158, 38, 3, STATIC);
	c23 = App->physics->CreateRectangle(307, 158, 37, 3, STATIC);
	c24 = App->physics->CreateRectangle(368, 158, 38, 3, STATIC);
	c25 = App->physics->CreateRectangle(468, 574, 10, 3, STATIC);
	c26 = App->physics->CreateRectangle(490, 574, 10, 3, STATIC);
	c33 = App->physics->CreateRectangle(490, 574, 10, 3, STATIC);
	inicio = App->physics->CreateRectangleSensor(480, 575, 10, 10);
	inicio->listener = this;

	//Points ball
	c27 = App->physics->CreateCircleBounce(185, 128, 12, STATIC);
	c27->ctype = ColliderType::POINTS;
	c27->listener = this;
	c28 = App->physics->CreateCircleBounce(244, 128, 12, STATIC);
	c28->ctype = ColliderType::POINTS;
	c28->listener = this;
	c29 = App->physics->CreateCircleBounce(307, 128, 12, STATIC);
	c29->ctype = ColliderType::POINTS;
	c29->listener = this;
	c30 = App->physics->CreateCircleBounce(368, 128, 12, STATIC);
	c30->ctype = ColliderType::POINTS;
	c30->listener = this;
	c31 = App->physics->CreateCircleBounce(185, 209, 12, STATIC);
	c31->ctype = ColliderType::POINTS;
	c31->listener = this;
	c32 = App->physics->CreateCircleBounce(368, 209, 12, STATIC);
	c32->ctype = ColliderType::POINTS;
	c32->listener = this;


	//Inicia otras colisiones
	Coll_Map();

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		sumar = true;
	}
	
	if (sumar == true) {
		puntos = puntos + 100;
		sumar = false;
	}
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
	/*if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8, DYNAMIC));
		circles.getLast()->data->listener = this;
	}*/

	//if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	circles.add(App->physics->CreateCircle(480, 560, 8, DYNAMIC));

	//	// Add this module (ModuleSceneIntro) as a "listener" interested in collisions with circles.
	//	// If Box2D detects a collision with this last generated circle, it will automatically callback the function ModulePhysics::BeginContact()
	//	circles.getLast()->data->listener = this;
	//}

	//	ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	//}

	// Prepare for raycast ------------------------------------------------------
	
	//Music update
	/*if (!muerto && !titlescene) {
		App->audio->PlayFx(music);
	}*/
	
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
	App->renderer->Blit(puntuation, 116, 623);
	App->renderer->Blit(point, 167, 110);
	App->renderer->Blit(point, 227, 110);
	App->renderer->Blit(point, 289, 110);
	App->renderer->Blit(point, 349, 110);
	App->renderer->Blit(point, 349, 190);
	App->renderer->Blit(point, 167, 190);
	App->renderer->Blit(bounce, 177, 390);

	if (puntos == 0) {
		App->renderer->Blit(barrapuntos, -298, 726);
	}
	if (puntos == 100) {
		App->renderer->Blit(barrapuntos, -285, 726);
	}
	if (puntos == 200) {
		App->renderer->Blit(barrapuntos, -250, 726);
	}
	if (puntos == 300) {
		App->renderer->Blit(barrapuntos, -215, 726);
	}
	if (puntos == 400) {
		App->renderer->Blit(barrapuntos, -174, 726);
	}
	if (puntos == 500) {
		App->renderer->Blit(barrapuntos, -139, 726);
	}
	if (puntos == 600) {
		App->renderer->Blit(barrapuntos, -100, 726);
	}
	if (puntos == 700) {
		App->renderer->Blit(barrapuntos, -60, 726);
	}
	if (puntos == 800) {
		App->renderer->Blit(barrapuntos, -25, 726);
	}
	if (puntos == 900) {
		App->renderer->Blit(barrapuntos, 10, 726);
	}
	if (puntos >= 1000) {
		App->renderer->Blit(barrapuntos, 45, 726);
		win = true;
	}
	
	App->renderer->Blit(maderita, 0, 714);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
		titlescene = false;
	}
	if (titlescene) {
		App->renderer->Blit(title, 0, 0);
	}
	else {

	}

	if (palancalefttex != NULL && !titlescene)
	{
		int x, y;
		palancaleft->GetPosition(x, y);
		App->renderer->Blit(palancalefttex, x+7, y-8, NULL, 0.2f, palancaleft->GetRotation()-30);
	}
	if (palancarighttex != NULL && !titlescene)
	{
		int x, y;
		palancaright->GetPosition(x, y);
		App->renderer->Blit(palancarighttex, x+4, y-8, NULL, 0.2f, palancaright->GetRotation()+30);
	}

	if (muerto) {
		App->renderer->Blit(losescreen, 0, 0);
		//music = NULL;
	}
	if (win == true) {
		SDL_DestroyTexture(App->player->balltex);
		SDL_DestroyTexture(App->player->ventilador);
		App->renderer->Blit(winscreen, 0, 0);
		App->player->ball->body->SetTransform(b2Vec2(9.6f, 11), 0);
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			SDL_DestroyTexture(winscreen);
			App->player->balltex = App->textures->Load("pinball/ball.png");
			App->player->ventilador = App->textures->Load("pinball/ventilador.png");
			App->renderer->Blit(App->player->ventilador, 466, 610);
			int x, y;
			App->player->ball->GetPosition(x, y);
			App->renderer->Blit(App->player->balltex, x, y, NULL, App->player->velshot, App->player->ball->GetRotation());
			win = false;
			puntos = 0;
		}
	}
	/*App->renderer->Blit(palancalefttex, 220, 523);
	App->renderer->Blit(palancarighttex, 290, 523);*/

	// Circles
	//p2List_item<PhysBody*>* c = circles.getFirst();
	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);

	//	// If mouse is over this circle, paint the circle's texture
	//	
	//	App->renderer->Blit(balltex, x, y, NULL, 1.0f, c->data->GetRotation());

	//	c = c->next;
	//}

	/*if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		b2Vec2 impulse = b2Vec2(0.0f, -1.0f);

		b2Vec2 point = circles->body->GetLocalCenter();
		circles->body->ApplyLinearImpulse(impulse, point, true);
	}*/

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

//Chain Collisions. Funcion para generar colisiones diagonals y curvas
void ModuleSceneIntro::Coll_Map() {

	p2List_item<PhysBody*>* temp = chains.getFirst();
	while (temp != NULL) {
		b2Body* body = temp->data->body;
		temp->data->body->GetWorld()->DestroyBody(body);
		temp = temp->next;
	}
	chains.clear();

	int diagonal01[8] = {
		0, 0,
		84, 48,
		80, 57,
		-4, 9
	};

	int diagonal02[8] = {
		0, 0,
		-86, 48,
		-82, 57,
		4, 9
	};

	int diagonal03[8] = {
		0, 0,
		50, 27,
		46, 36,
		-4, 9
	};

	int diagonal04[8] = {
		0, 0,
		-50, 28,
		-46, 37,
		4, 9
	};

	int diagonal05[8] = {
		0, 0,
		120, 65,
		115, 75,
		-4, 9
	};

	int diagonal06[8] = {
		0, 0,
		-120, 65,
		-115, 75,
		4, 9
	};

	int diagonal07[12] = {
		0, 0,
		-35, 32,
		-31, 41,
		-1, 11,
		9, 22,
		16, 14
	};

	int diagonal08[8] = {
		0, 0,
		40, 38,
		31, 45,
		-4, 9
	};

	int diagonal09[12] = {
		0, 0,
		40, 22,
		33, 25,
		0, 9,
		-33, 25,
		-40, 22
	};

	int diagonal10[30] = {
		0, 0,
		20, 0,
		60, 6,
		100, 22,
		140, 45,
		180, 85,
		200, 118,
		210, 139,
		208, -5,
		-160, -5,
		-160, 65,
		-140, 48,
		-100, 22,
		-60, 6,
		-20, 0
	};

	int boing01[18] = {
		0, 0,
		20, -30,
		24, -31,
		27, -29,
		29, -26,
		28, 5,
		25, 9,
		0, 11,
		-3, 5
	};

	int boing02[18] = {
		0, 0,
		-20, -30,
		-24, -31,
		-27, -29,
		-29, -26,
		-28, 5,
		-25, 9,
		0, 11,
		3, 5
	};

	botibotis.add(App->physics->CreateChainBumper(345, 425, boing01, 18));
	botibotis.add(App->physics->CreateChainBumper(209, 425, boing02, 18));
	

	chains.add(App->physics->CreateChain(130, 470, diagonal01, 8));
	chains.add(App->physics->CreateChain(422, 470, diagonal02, 8));
	chains.add(App->physics->CreateChain(166, 439, diagonal03, 8));
	chains.add(App->physics->CreateChain(385, 439, diagonal04, 8));
	chains.add(App->physics->CreateChain(94, 520, diagonal05, 8));
	chains.add(App->physics->CreateChain(460, 520, diagonal06, 8));
	chains.add(App->physics->CreateChain(127, 289, diagonal07, 12));
	chains.add(App->physics->CreateChain(385, 140, diagonal08, 8));
	chains.add(App->physics->CreateChain(278, 205, diagonal09, 12));
	chains.add(App->physics->CreateChain(282, 35, diagonal10, 30));

}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
	// Play Audio FX on every collision, regardless of who is colliding
	//App->audio->PlayFx(bonus_fx);
	/*switch (bodyB->ctype)
	{
		case ColliderType::LOSE:
			App->audio->PlayFx(App->audio->hit_ball);
			App->textures->Unload(balltex);
			break;
	}*/
	
	LOG("Toydentro")

	/*if (bodyB->ctype == ColliderType::BALL && bodyA->ctype == ColliderType::LOSE) {
		App->audio->PlayFx(App->audio->hit_ball);
	}*/

	if (bodyB == s1) {
		losescreen = App->textures->Load("pinball/losescreen.png");
		App->audio->Init();
		if (solouno == false) {
			App->audio->PlayFx(dead_fx);
		}
		solouno = true;
		muerto = true;
		puntos = 0;
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			App->player->ball->body->SetTransform(b2Vec2(9.6f, 11), 0);
			SDL_DestroyTexture(losescreen);
			muerto = false;
		}
	}

	if (sumar == false) {
		if (bodyB->ctype==ColliderType::POINTS) {
			sumar = true;
		}
	}
	

	if (bodyB == inicio) {
		App->player->soplar = true;
	}


	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}
