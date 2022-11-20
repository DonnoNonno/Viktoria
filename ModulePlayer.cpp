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
	//Texturas
	balltex = App->textures->Load("pinball/ball.png");
	ventilador = App->textures->Load("pinball/ventilador.png");
	air = App->textures->Load("pinball/air.png");

	ball = (App->physics->CreateCircle(480, 560, 8, DYNAMIC));
	ball->ctype = ColliderType::BALL;
	
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
	if (!App->scene_intro->titlescene && !App->scene_intro->muerto) {
		//Ball
		if (ball != NULL) {
			int x, y;
			ball->GetPosition(x, y);
			App->renderer->Blit(balltex, x, y, NULL, 1.0f, ball->GetRotation());
		}

		//Ventilador
		App->renderer->Blit(ventilador, 466, 610);
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->renderer->Blit(air, 466, 585);

		//Palancas
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->scene_intro->palancaleft->body->ApplyTorque(-40.0f, true);
		else
			App->scene_intro->palancaleft->body->ApplyTorque(5.0f, true);

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			App->scene_intro->palancaright->body->ApplyTorque(40.0f, true);
		else
			App->scene_intro->palancaright->body->ApplyTorque(-5.0f, true);
	}
	
	return UPDATE_CONTINUE;
}



