#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

// Game Settings
#define FRAMESTEP 30.f
#define PLAYER_SPEED 3.f
#define ACCELERATION 0.1f
#define MAXSPEED 3.f
#define JUMPTIME 4.f
#define INTRO_SCENE_DURATION 10.f
#define BLUR_DOWNSAMPLE 4.0f
#define PLAYER_GROUND_OFFSET 1.f
#define MORPH_WALK_SPEED 5.f

#define CAMERA_THIRD_PERSON_OFFSET 20.f
#define CAMERA_THIRD_PERSON_Y_OFFSET 20.f
#define CAMERA_FIRST_PERSON_OFFSET 3.f

// Windowing
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
//#define WINDOW_WIDTH 1600
//#define WINDOW_HEIGHT 900

#define WINDOWED sf::Style::Default
#define FULLSCREEN sf::Style::Fullscreen

#define DEFAULT_WINDOW_MODE WINDOWED

#define SFML_DEPTH_BITS 32
#define SFML_ANTI_ALIAS 0
#define SFML_VERTICAL_SYNC false
#define SFML_CURSOR_VISIBLE false

// OpenGl
//#define CLEAR_COLOR 0.f, 0.f, 0.f, 1.f
#define CLEAR_COLOR 0.298f, 0.704f, 1.0f, 1.f
#define FOV_DEGREE 120.f
#define FOV_NEAR 1.f
#define FOV_FAR 2000.f

// Text
#define STUDIO				"Gamesmiths"
#define GAME_TITLE			"Monkey Racers"

//// Files

#define RES_PATH_MAZE		"Resources/Models/Environment/Maze/"
#define RES_PATH_ISLAND		"Resources/Models/Environment/Island/"

// OBJs
#define OBJ_LEVEL_TEST1		"Resources/Models/Environment/monkey_world1.obj"
#define OBJ_LEVEL_EX_STAGE2	"Resources/Models/Environment/example_stage2.obj"
#define OBJ_LEVEL_ISLAND	"Resources/Models/Environment/Island/Island.obj"

#define OBJ_MONKEY0			"Resources/Models/Characters/Monkey0.obj"
#define OBJ_MONKEY1			"Resources/Models/Characters/Monkey1.obj"
#define OBJ_MONKEY2			"Resources/Models/Characters/Monkey2.obj"
#define OBJ_MONKEY3			"Resources/Models/Characters/Monkey3.obj"
#define OBJ_MONKEY4			"Resources/Models/Characters/Monkey4.obj"
#define OBJ_MONKEY5			"Resources/Models/Characters/Monkey5.obj"
#define OBJ_MONKEY6			"Resources/Models/Characters/Monkey6.obj"

#define OBJ_MONKEY_WALK1	"Resources/Models/Characters/Monkey_walk1.obj"
#define OBJ_MONKEY_WALK2	"Resources/Models/Characters/Monkey_walk2.obj"
#define OBJ_MONKEY_WALK3	"Resources/Models/Characters/Monkey_walk3.obj"
#define OBJ_MONKEY_WALK4	"Resources/Models/Characters/Monkey_walk4.obj"
#define OBJ_MONKEY_WALK5	"Resources/Models/Characters/Monkey_walk5.obj"
#define OBJ_MONKEY_WALK6	"Resources/Models/Characters/Monkey_walk6.obj"
#define OBJ_MONKEY_WALK7	"Resources/Models/Characters/Monkey_walk7.obj"
#define OBJ_MONKEY_WALK8	"Resources/Models/Characters/Monkey_walk8.obj"

#define OBJ_MONKEY_LOW		"Resources/Models/Characters/Monkey_Low.obj"
#define OBJ_BLOOD_FOUNTAIN	"Resources/Models/Props/BloodFountainV3.obj"
#define OBJ_CUBE			"Resources/Models/Primitives/cube.obj"
#define OBJ_PLANE			"Resources/Models/Primitives/plane.obj"
#define OBJ_ROCKA			"Resources/Models/Environment/Island/rocka.obj"
#define OBJ_ROCKB			"Resources/Models/Environment/Island/rockb.obj"

#define OBJ_POWERUP_COCONUT "Resources/Models/Props/coconut.obj"

#define OBJ_TRIGGER_EXIT	"Resources/Models/Environment/Island/triggerExit.obj"

// Textures
#define TEX_UV_HELPER_BW	"Resources/Textures/CbxKs.jpg"
#define TEX_UV_HELPER_COL	"Resources/Textures/uvchecker.jpg"

#define TEX_ISLAND			"Resources/Textures/Environment/terrain6_u1_v1.png"
#define TEX_OCEAN			"Resources/Textures/Environment/ocean.jpg"
//#define TEX_WALL			"Resources/Textures/Environment/wall.png"
#define TEX_PALM_TREE		"Resources/Textures/Environment/palmTree.png"
#define TEX_SPHERE_TREE		"Resources/Textures/Environment/sphereTree.png"
#define TEX_CONE_TREE		"Resources/Textures/Environment/coneTree.png"
#define TEX_BOAT			"Resources/Textures/Environment/boat.png"
//#define TEX_GRASSY_GROUND	"Resources/Textures/Environment/grass.png"
#define TEX_DOCK			"Resources/Textures/Environment/Dock.jpg"
#define TEX_SKY_UP			"Resources/Textures/Environment/up.jpg"
#define TEX_SKY_DOWN		"Resources/Textures/Environment/dn.jpg"
#define TEX_SKY_LEFT		"Resources/Textures/Environment/lt.jpg"
#define TEX_SKY_RIGHT		"Resources/Textures/Environment/rt.jpg"
#define TEX_SKY_FRONT		"Resources/Textures/Environment/ft.jpg"
#define TEX_SKY_BACK		"Resources/Textures/Environment/bk.jpg"

#define TEX_MONKEY			"Resources/Textures/Characters/monkey.png"
//#define TEX_BLOOD_FOUNTAIN	"Resources/Textures/Props/BloodFountain.jpg"
#define TEX_COCONUT			"Resources/Textures/Props/coconut.jpg"
#define TEX_FENCE			"Resources/Textures/Props/fence_diffuse.png"
#define TEX_BARREL			"Resources/Textures/Props/barrel_diffuse.png"
#define TEX_SIGN			"Resources/Textures/Props/sign_diffuse.png"
//#define TEX_SPIKES			"Resources/Textures/Props/spikes texture.png"
#define TEX_ROCK1			"Resources/Textures/Props/rocka.jpg"
#define TEX_ROCK2			"Resources/Textures/Props/rockb.jpg"
#define TEX_GRASS			"Resources/Textures/Props/grass.png"
//#define TEX_YELLOW			"Resources/Textures/Environment/yellow.jpg"
#define TEX_MOLTEN			"Resources/Textures/Props/Lava_and_Rock_Study_1_by_Devin_Busha.jpg"

#define TEX_PART1			"Resources/Textures/Particles/part1.jpg"
#define TEX_PART_FIRE		"Resources/Textures/Particles/fireball.png"
#define TEX_PART_SMOKE		"Resources/Textures/Particles/partSmoke.png"

#define TEX_PART_SCORE_1000	"Resources/Textures/Particles/score1000.png"
#define TEX_SHADER_QMAP		"Resources/Textures/qMap.png"

// Audio
#define SOUND_BUMP1			"Resources/Audio/Sounds/18758__tilde__famikick.wav"
#define SOUND_BUMP2			"Resources/Audio/Sounds/170141__timgormly__8-bit-bump.aiff"
#define SOUND_POWERUP		"Resources/Audio/Sounds/77245__studiocopsey__power-up.wav"
#define SOUND_POWERUP2		"Resources/Audio/Sounds/coconut collect.mp3"
#define SOUND_FALL			"Resources/Audio/Sounds/147262__iedlabs__8bit-pitchslide-down.wav"
#define SOUND_BUMP			"Resources/Audio/Sounds/Crash.mp3"
#define SOUND_MENU_OPEN		"Resources/Audio/Sounds/simple tone.mp3"
#define SOUND_MENU_CLICK	"Resources/Audio/Sounds/Menu click.mp3"
#define SOUND_BEGIN			"Resources/Audio/Sounds/begin.mp3"
#define SOUND_TRY_AGAIN		"Resources/Audio/Sounds/Try Again.mp3"
#define SOUND_FINISH		"Resources/Audio/Sounds/Finish.mp3"
#define SOUND_HURRY			"Resources/Audio/Sounds/hurry up.mp3"
#define SOUND_EXPLOSION		"Resources/Audio/Sounds/199732__omar-alvarado__expl8.mp3"

#define MUSIC_G8			"Resources/Audio/Music/177089__questiion__lost-moon-s-greatful-eight-s.ogg"
#define MUSIC_AGB			"Resources/Audio/Music/177085__questiion__lost-moon-s-anti-gravity-burial.ogg"
#define MUSIC_SAAB			"Resources/Audio/Music/166393__questiion__lost-moons-serious-as-an-attack-button.ogg"
#define MUSIC_MEAG			"Resources/Audio/Music/166392__questiion__8bit-blix-aka-lost-moons-make-me-a-game-snippet-notify-if-longer-version-is-needed.ogg"

// Paths
#define PATH_CAMERA_INTRO	"Resources/Models/Environment/Maze/Paths/CameraIntro.txt"
#define PATH_COCONUT_TRAIL	"Resources/Models/Environment/Island/Paths/CoconutTrail.txt"
#define PATH_ROCK_FALL		"Resources/Models/Environment/Island/Paths/FallingRockPoints.txt"

// Lighting
#define LIGHT_AMBIENT_COL {0.2f, 0.2f, 0.2f, 1.f}
#define LIGHT_DEFUSE_COL {0.992f, 0.722f, 0.075f, 1.f}
#define LIGHT_SPECULAR_COL {0.992f, 0.722f, 0.075f, 1.f};
#define LIGHT_AMBIENT_COL1 {0.1f, 0.1f, 0.1f, 1.f}
#define LIGHT_DEFUSE_COL1 {.3f, .3f, .3f, 1.f}
#define LIGHT_SPECULAR_COL1 {.5f, .5f, .5f, 1.f};

// Shaders
#define V_SHADER_PASS_TEX_COORD "Resources/Shaders/passTexcoord_ndc_v.glsl"
#define V_SHADER_PASS_ATTRIB	"Resources/Shaders/passAttribs_v.glsl"
#define V_SHADER_P_PASS_ATTRIB	"Resources/Shaders/particle_passAttribs_v.glsl"

#define F_SHADER_PASSTHROUGH	"Resources/Shaders/passthrough_f.glsl"
#define F_SHADER_CELSHADING		"Resources/Shaders/celShading_f.glsl"
#define F_SHADER_PHONG			"Resources/Shaders/phongLighting_f.glsl"
#define F_SHADER_OUTLINES		"Resources/Shaders/postOutlines_f.glsl"
#define F_SHADER_BRIGHT_TONE	"Resources/Shaders/brightTone_f.glsl"
#define F_SHADER_BOX_BLUR		"Resources/Shaders/boxBlur_f.glsl"
#define F_SHADER_GAUSS_BLUR_2D  "Resources/Shaders/gaussBlur2D_f.glsl"
#define F_SHADER_GAUSS_BLUR_X   "Resources/Shaders/gaussBlurX_f.glsl"
#define F_SHADER_GAUSS_BLUR_Y   "Resources/Shaders/gaussBlurY_f.glsl"
#define F_SHADER_ADDITIVE		"Resources/Shaders/additive_f.glsl"
#define F_SHADER_MB_BLEND		"Resources/Shaders/Motion Blur/blend_f.glsl"
#define F_SHADER_MB_SS			"Resources/Shaders/Motion Blur/motionBlur_f.glsl"
#define F_SHADER_PARTICLE		"Resources/Shaders/particle_f.glsl"
#define F_SHADER_PARTICLE_COMP	"Resources/Shaders/particle_composite_f.glsl"


#endif