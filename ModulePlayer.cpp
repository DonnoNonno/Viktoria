#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
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
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->scene_intro->palancaleft->body->ApplyTorque(-60.0f, true);
	else
		App->scene_intro->palancaleft->body->ApplyTorque(15.0f, true);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->scene_intro->palancaright->body->ApplyTorque(60.0f, true);
	else
		App->scene_intro->palancaright->body->ApplyTorque(-15.0f, true);
	
	return UPDATE_CONTINUE;
}



