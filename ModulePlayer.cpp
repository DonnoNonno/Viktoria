#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	balltex = App->textures->Load("pinball/ball.png");
	ball = (App->physics->CreateCircle(480, 560, 8, DYNAMIC));
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	ball = nullptr;
	balltex = nullptr;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if (ball != NULL) {
		int x, y;
		ball->GetPosition(x, y);
		App->renderer->Blit(balltex, x, y, NULL, 1.0f, ball->GetRotation());
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->scene_intro->palancaleft->body->ApplyTorque(-40.0f, true);
	else
		App->scene_intro->palancaleft->body->ApplyTorque(5.0f, true);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->scene_intro->palancaright->body->ApplyTorque(40.0f, true);
	else
		App->scene_intro->palancaright->body->ApplyTorque(-5.0f, true);
	
	return UPDATE_CONTINUE;
}



