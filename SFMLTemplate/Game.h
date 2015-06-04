#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include "Model.h"
#include "Camera3D.h"
//#include "ParticleEngine.h"
#include "AStarPathfinder.h"

#define THIRD_PERSON 0
#define FIRST_PERSON 1

class Game
{
public:
	Game();
	void init();
	void run();
	void processEvents();
	void update();
	void draw();
	void drawGUI();

	void reset();
	//morph targets
	void updateAllAnimations();
	void nextAnimation();

	//intro scene
	void playIntro();
	void stopIntro();

	//Moder OpenGL
	const bmath::mat::mat4 ObjectLookAt(Object *obj, const bmath::vec::vec3 position, 
		const bmath::vec::vec3 worldUp, const bmath::vec::vec3 focalPoint);
	const bmath::mat::mat4 ObjectLookAt(Object *obj, const float positionX, const float positionY, const float positionZ, 
		const float worldUpX, const float worldUpY, const float worldUpZ, const float focalPointX, const float focalPointY,
		const float focalPointZ);
	void UpdateCameraMatrices();
	void UpdateObjectMatrices(const Object *obj);
	void SetupAndDraw( Object *obj, bmath::vec::vec4 lightPosWorld, bmath::vec::vec4 eyePosWorld);

private:
	// In-game settings
	GLint polyMode;
	bool cameraType;
	bool musicOn;
	bool blurOn;
	//bool debugPrintPaths;

	sf::Clock clock;
	sf::Clock particleClock;

	sf::Window window;
	sf::Event event;

	Camera3D* cam;
	float camOffsetAzumuth;
	float camOffsetElevation;

	sf::Mouse mouse;
	//ParticleEngine* particleEngine;
	//ParticleEngine* particlePath;
	ParticleSystem* particleSystem;
	Vec3 spawnPoint;

	// Objects
	Model* island;
	Model* player;
	Model* monkeyMT0;
	Model* monkeyMT1;
	Model* monkeyMT2;
	Model* monkeyMT3;
	Model* monkeyMT4;
	Model* monkeyMT5;
	Model* monkeyMT6;
	Model* monkeyMT7;
	Model* monkeyMT8;

	Model* testModel;

	int monkeyAnimation;

	SkyBox sky;
	std::vector<Object*> collisionObjects;
	std::vector<Object*> floor;
	std::vector<Object*> objects;
	std::vector<Object*> powerUps;
	std::vector<Object*> traps;

	std::vector<Object*> fallingRocks;
	std::vector<Object*> spawnedFallingRocks;
	std::vector<Vec3> spawnedFallingRocksDest;
	std::vector<bool> spawnedFallingRocksGrounded;
	std::vector<float> spawnedFallingRocksVelocity;
	//std::vector<Object*> spawnedFallingRocksCollision;

	Model* triggerExit;

	// Textures
	GLuint texIsland;
	GLuint texMonkey;
	GLuint texUVHelper;
	GLuint texPart;
	GLuint texPartFire;
	GLuint texPartSmoke;
	GLuint texCoconut;
	GLuint texFence;
	GLuint texBarrel;
	GLuint texSign;
	GLuint texPalmTree;
	GLuint texSphereTree;
	GLuint texConeTree;
	GLuint texGrass;
	GLuint texRockA;
	GLuint texRockB;
	GLuint texQMap;
	GLuint texPartScore1000;
	GLuint texMolten;


	// Hud
	HUD* hud;
	long score;

	// Physics
	float acceleration;
	Vec3 velocity;
	float maxSpeed;
	float jumpTime;

	//// Pathfinding
	//std::vector<std::vector<PathNode*>> pathNodes;
	//AStarPathFinder* astar;

	//float tileSizeX;
	//float tileSizeY;
	//float gridSizeX;
	//float gridSizeY;
	//float tileStartX;
	//float tileStartY;

	// Flags
	bool hasCollided;
	bool fallingSoundPlaying;
	bool collisionSoundPlaying;
	bool hurryUpPlayed;

	bool levelComplete;
	bool canJump;
	bool isPlayingIntro;
	bool isAnimating;

	// Sounds
	//sf::SoundBuffer soundBump1;
	//sf::SoundBuffer soundBump2;
	//sf::SoundBuffer soundPowerUp;
	//sf::SoundBuffer soundFall;
	//sf::Sound sound;
	//sf::Music music1;

	sound soundBump;
	sound soundBump1;
	sound soundBump2;
	sound soundPowerUp;
	sound soundFall;
	sound soundExplosion;
	sound soundMenuClick;
	sound soundMenuOpen;
	sound soundBegin;
	sound soundTryAgain;
	sound soundFinish;
	sound soundHurryUp;

	sound music1;

	Path path;
	Path pathCameraIntro;

	Path pathCoconutTrail;
	Path pathRockFall;

	// morphing
	Model* target;
	Model* result;

	//NEW
	// pipeline transforms
	bmath::mat::mat4 modelMat;
	bmath::mat::mat4 viewMat;
	bmath::mat::mat4 projectionMat;

	// concatenated
	bmath::mat::mat4 modelViewMat;
	bmath::mat::mat4 prevViewProjectionMat;
	bmath::mat::mat4 viewProjectionMat;
	bmath::mat::mat4 modelViewProjectionMat;

	// inverse
	bmath::mat::mat4 eyeToWorld;
	bmath::mat::mat4 worldToObject;

	bool startupPlayed;

	std::vector<ParticleSystem*> environParticles;
	std::vector<ParticleSystem*> tempParticles;
};

#endif