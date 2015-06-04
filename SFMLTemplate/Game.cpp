#include "Engine.h"
#include "MenuManager.h"
#include "AStarPathfinder.h"
#include "HelpMe.h"

#pragma region Shaders
cbmini::cbfw::FrameBuffer* sceneFBO = new cbmini::cbfw::FrameBuffer;
cbmini::cbfw::FrameBuffer* particleFBO = new cbmini::cbfw::FrameBuffer;
cbmini::cbfw::FrameBuffer* blurFBO1 = new cbmini::cbfw::FrameBuffer;
cbmini::cbfw::FrameBuffer* blurFBO2 = new cbmini::cbfw::FrameBuffer;
cbmini::cbfw::FrameBuffer* outlinesFBO = new cbmini::cbfw::FrameBuffer;
cbmini::cbfw::FrameBuffer* brightFBO = new cbmini::cbfw::FrameBuffer;
cbmini::cbfw::FrameBuffer* motionBlurFBO = new cbmini::cbfw::FrameBuffer;

cbmini::cbfw::VertexBuffer *fsqPlane = new cbmini::cbfw::VertexBuffer;

cbmini::cbfw::GLSLProgram* celShader;
cbmini::cbfw::GLSLProgram* postOutlines;
cbmini::cbfw::GLSLProgram* curShader;
cbmini::cbfw::GLSLProgram* passThroughShader;
cbmini::cbfw::GLSLProgram *boxBlurShader;
cbmini::cbfw::GLSLProgram *gaussBlur2DShader;
cbmini::cbfw::GLSLProgram *gaussBlurXShader;
cbmini::cbfw::GLSLProgram *gaussBlurYShader;
cbmini::cbfw::GLSLProgram *brightToneShader;
cbmini::cbfw::GLSLProgram *additiveShader;
cbmini::cbfw::GLSLProgram *particleCompositeShader;
cbmini::cbfw::GLSLProgram *motionBlendShader;
cbmini::cbfw::GLSLProgram *motionBlurShader;
cbmini::cbfw::GLSLProgram *particleShader;

int sceneImg;
void CreatePassthroughShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_PASSTHROUGH);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	sceneImg = program->GetUniformLocation("sceneImg");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(sceneImg, 0);
	program->Deactivate();
}

int csMVP, csEyePos, csLightPos, csLightCol, csDiffuseTex, csQMapTex;
void CreateCelShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_ATTRIB);
	frag.CreateFromFile(fragType, F_SHADER_CELSHADING);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	csMVP = program->GetUniformLocation("mvp");
	csEyePos = program->GetUniformLocation("eyePos");
	csLightPos = program->GetUniformLocation("lightPos");
	csLightCol = program->GetUniformLocation("lightCol");
	csDiffuseTex = program->GetUniformLocation("diffuseTex");
	csQMapTex = program->GetUniformLocation("qMapTex");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(csDiffuseTex, 0);
	glUniform1i(csQMapTex, 1);
	program->Deactivate();
}
int pModelView, pProj, pDiffuseTex, pSize;
void CreateParticleShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag, geom;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag, *geomPtr=&geom;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;
	const cbmini::cbfw::ShaderType geomType = cbmini::cbfw::GLSL_GEOMETRY_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_P_PASS_ATTRIB);
	frag.CreateFromFile(fragType, F_SHADER_PARTICLE);
	geom.CreateFromFile(geomType, "Resources/Shaders/particle_g.glsl");
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);
	program->AttachShader(geomPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	pModelView = program->GetUniformLocation("modelView");
	pProj = program->GetUniformLocation("proj");
	pDiffuseTex = program->GetUniformLocation("diffuseTex");
	pSize = program->GetUniformLocation("partSize");

	vert.Release();
	frag.Release();
	geom.Release();

	program->Activate();
	glUniform1i(pDiffuseTex, 0);
	program->Deactivate();
}
void CreatePhongShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_ATTRIB);
	frag.CreateFromFile(fragType, F_SHADER_PHONG);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();


	// ******** 
	// uniforms
	csMVP = program->GetUniformLocation("mvp");
	csEyePos = program->GetUniformLocation("eyePos");
	csLightPos = program->GetUniformLocation("lightPos");
	csLightCol = program->GetUniformLocation("lightCol");
	csDiffuseTex =  program->GetUniformLocation("diffuseTex");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(csDiffuseTex, 0);
	program->Deactivate();
}

int poPixelSize, poLineWidth, poSceneDiffuse, poSceneNormals, poSceneDepth;
void CreateOutlinesProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_OUTLINES);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	poPixelSize = program->GetUniformLocation("pixelSize");
	poLineWidth = program->GetUniformLocation("lineWidth");
	poSceneDiffuse = program->GetUniformLocation("sceneDiffuse");
	poSceneNormals = program->GetUniformLocation("sceneNormals");
	poSceneDepth = program->GetUniformLocation("sceneDepth");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform2f(poPixelSize, 1.0f/WINDOW_WIDTH, 1.0f/WINDOW_HEIGHT);
	glUniform1f(poLineWidth, 1.0f);
	glUniform1i(poSceneDiffuse, 0);
	glUniform1i(poSceneNormals, 1);
	glUniform1i(poSceneDepth, 2);
	program->Deactivate();
}

void CreateBrightToneShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_BRIGHT_TONE);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	sceneImg = program->GetUniformLocation("sceneImg");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(sceneImg, 0);
	program->Deactivate();
}
int bbPixelSize;
void CreateBoxBlurProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_BOX_BLUR);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	sceneImg = program->GetUniformLocation("sceneImg");
	bbPixelSize = program->GetUniformLocation("pixelSize");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(sceneImg, 0);
	glUniform2f(bbPixelSize, 
		1.0f/WINDOW_WIDTH, 
		1.0f/WINDOW_HEIGHT);
	program->Deactivate();
}
void CreateGaussBlur2DProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_GAUSS_BLUR_2D);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	sceneImg = program->GetUniformLocation("sceneImg");
	bbPixelSize = program->GetUniformLocation("pixelSize");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(sceneImg, 0);
	glUniform2f(bbPixelSize, 
		1.0f/WINDOW_WIDTH, 
		1.0f/WINDOW_HEIGHT);
	program->Deactivate();
}

void CreateGaussBlurXProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_GAUSS_BLUR_X);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	sceneImg = program->GetUniformLocation("sceneImg");
	bbPixelSize = program->GetUniformLocation("pixelSize");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(sceneImg, 0);
	glUniform2f(bbPixelSize, 
		1.0f/WINDOW_WIDTH, 
		1.0f/WINDOW_HEIGHT);
	program->Deactivate();
}

void CreateGaussBlurYProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_GAUSS_BLUR_Y);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	sceneImg = program->GetUniformLocation("sceneImg");
	bbPixelSize = program->GetUniformLocation("pixelSize");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(sceneImg, 0);
	glUniform2f(bbPixelSize, 
		1.0f/WINDOW_WIDTH, 
		1.0f/WINDOW_HEIGHT);
	program->Deactivate();
}

int scSceneImg, scPostProcImg;
void CreateAdditiveShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_ADDITIVE);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	scSceneImg = program->GetUniformLocation("sceneImg");
	scPostProcImg = program->GetUniformLocation("postProcImg");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(scSceneImg, 0);
	glUniform1i(scPostProcImg, 1);
	program->Deactivate();
}

int mbSceneImg1, mbSceneImg2, mbSceneImg3, mbSceneImg4;
void CreateBlendShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_MB_BLEND);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	mbSceneImg1 = program->GetUniformLocation("sceneImg1");
	mbSceneImg2 = program->GetUniformLocation("sceneImg2");
	mbSceneImg3 = program->GetUniformLocation("sceneImg3");
	mbSceneImg4 = program->GetUniformLocation("sceneImg4");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(mbSceneImg1, 0);
	glUniform1i(mbSceneImg2, 1);
	glUniform1i(mbSceneImg3, 2);
	glUniform1i(mbSceneImg4, 3);
	program->Deactivate();
}

int mbDiffuse, mbDepth, mbInvVP, mbPrevVP;
void CreateMotionBlurShaderProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_MB_SS);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	mbDiffuse = program->GetUniformLocation("sceneDiffuse");
	mbDepth = program->GetUniformLocation("sceneDepth");
	mbInvVP = program->GetUniformLocation("inverseViewProj");
	mbPrevVP = program->GetUniformLocation("prevViewProj");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(mbDiffuse, 0);
	glUniform1i(mbDepth, 1);
	program->Deactivate();
}

int pcSceneImg, pcPartImg, pcSceneDepth, pcPartDepth;
void CreateParticleCompositeProgram(cbmini::cbfw::GLSLProgram *program)
{
	cbmini::cbfw::GLSLShader vert, frag;
	cbmini::cbfw::GLSLShader *vertPtr=&vert, *fragPtr=&frag;
	const cbmini::cbfw::ShaderType vertType = cbmini::cbfw::GLSL_VERTEX_SHADER;
	const cbmini::cbfw::ShaderType fragType = cbmini::cbfw::GLSL_FRAGMENT_SHADER;

	vert.CreateFromFile(vertType, V_SHADER_PASS_TEX_COORD);
	frag.CreateFromFile(fragType, F_SHADER_PARTICLE_COMP);
	program->AttachShader(vertPtr);
	program->AttachShader(fragPtr);

	program->LinkProgram();

	// ******** 
	// uniforms
	pcSceneImg = program->GetUniformLocation("sceneImg");
	pcPartImg = program->GetUniformLocation("partImg");
	pcSceneDepth = program->GetUniformLocation("sceneDepth");
	pcPartDepth = program->GetUniformLocation("partDepth");

	vert.Release();
	frag.Release();

	program->Activate();
	glUniform1i(pcSceneImg, 0);
	glUniform1i(pcPartImg, 1);
	glUniform1i(pcSceneDepth, 2);
	glUniform1i(pcPartDepth, 3);
	program->Deactivate();
}

#pragma endregion

Game::Game()
{
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = SFML_DEPTH_BITS;
	contextSettings.antialiasingLevel = SFML_ANTI_ALIAS;

	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, DEFAULT_WINDOW_MODE, contextSettings);

	window.setVerticalSyncEnabled(SFML_VERTICAL_SYNC);
	window.setMouseCursorVisible(SFML_CURSOR_VISIBLE);

	cam = new Camera3D(&window);

	polyMode = GL_FILL;
	cameraType = THIRD_PERSON;
	musicOn = true;
	blurOn = false;

	acceleration = ACCELERATION;
	maxSpeed = MAXSPEED;
	jumpTime = JUMPTIME;

	score = 0;
	levelComplete = false;

	hasCollided = false;
	collisionSoundPlaying = false;

	canJump = true;
	isPlayingIntro = false;

	spawnPoint = Vec3(190, 195, 90);
	//spawnPoint = Vec3(471, 14, 66);

	result = new Model();

	camOffsetAzumuth = camOffsetElevation = 0;

	startupPlayed = false;
	hurryUpPlayed = false;
}

void Game::run()
{
	init();
	//playIntro();
	sf::Clock frameClock;
	sf::Time lastUpdate = sf::Time::Zero;

	static sf::Time timePerFrame = sf::seconds(1 / FRAMESTEP);
	while (window.isOpen())
	{

		lastUpdate += frameClock.restart();

		// restrict fps to framestep
		while (lastUpdate > timePerFrame)
		{
			lastUpdate -= timePerFrame;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// override user input when menu is displayed
			if (!GameSmithsMenuManager::ManageMenus(&window, &event, soundMenuClick)) 
			{
				if (!startupPlayed)
				{
					//playIntro();
					startupPlayed = true;

					soundBegin.playDawg();
					music1.playDawg();
					particleSystem->Start();
				}
				hud->SetGameState(HUD::RUNNING);

				isAnimating = true;

				//if (music1.getStatus() == sf::SoundSource::Status::Paused && musicOn)
					//music1.playDawg();

				if (!isPlayingIntro && !levelComplete)
				{
					processEvents();
				}
				else if (isPlayingIntro)
				{
					hud->SetGameState(HUD::INIT);
					Vec3 tempPos = path.GetCurrentState();

					player->pos.x = tempPos.x;
					player->pos.z = tempPos.z;
					player->pos.y = tempPos.y;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
					{
						stopIntro();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}
				}
				else
				{
					isAnimating = false;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					{
						reset();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}
				}
			}
			else
			{
				isAnimating = false;
				//music1.pause();
				hud->SetGameState(hud->PAUSED);
			}

			update();
		}
		draw();

		window.display();
	}

	delete monkeyMT0;
	delete monkeyMT1;
	delete monkeyMT2;
	delete monkeyMT3;
	delete monkeyMT4;
	delete monkeyMT5;
	delete monkeyMT6;
	delete monkeyMT7;
	delete monkeyMT8;
	delete result;
	delete island;

	collisionObjects.clear();
	objects.clear();
	powerUps.clear();
	delete triggerExit;
	delete cam;
	//delete particleSystem;
	environParticles.clear();
	tempParticles.clear();

	fallingRocks.clear();
	spawnedFallingRocks.clear();
	spawnedFallingRocksDest.clear();
	spawnedFallingRocksGrounded.clear();
	spawnedFallingRocksVelocity.clear();
	//spawnedFallingRocksCollision.clear();

	soundBump.release();
	soundBump1.release();
	soundBump2.release();
	soundPowerUp.release();
	soundFall.release();
	soundExplosion.release();
	soundMenuOpen.release();
	soundMenuClick.release();
	soundBegin.release();
	soundTryAgain.release();
	soundFinish.release();
	soundHurryUp.release();
	music1.release();
}

void Game::init()
{
	glewInit();
	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(CLEAR_COLOR);

	// Enable Z-buffer read and write (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	projectionMat = bmath::mat::makePerspective(deg2radf*FOV_DEGREE, WINDOW_WIDTH/WINDOW_HEIGHT, FOV_NEAR, FOV_FAR);
	glLoadMatrixf(projectionMat.m);

	Model* obj1;

	// Load Textures
	texMonkey = loadTexture(TEX_MONKEY);
	texUVHelper = loadTexture(TEX_UV_HELPER_BW);
	texPart = loadTexture(TEX_PART1);
	texPartFire = loadTexture(TEX_PART_FIRE);
	texPartSmoke = loadTexture(TEX_PART_SMOKE);
	texPartScore1000 = loadTexture(TEX_PART_SCORE_1000);
	texCoconut = loadTexture(TEX_COCONUT);
	texFence = loadTexture(TEX_FENCE);
	texBarrel = loadTexture(TEX_BARREL);
	texSign = loadTexture(TEX_SIGN);
	texPalmTree = loadTexture(TEX_PALM_TREE);
	texSphereTree = loadTexture(TEX_SPHERE_TREE);
	texConeTree = loadTexture(TEX_CONE_TREE);
	texGrass = loadTexture(TEX_GRASS);
	texIsland = loadTexture(TEX_ISLAND);
	texRockA = loadTexture(TEX_ROCK1);
	texRockB = loadTexture(TEX_ROCK2);
	texMolten = loadTexture(TEX_MOLTEN);

	texQMap = loadTexture(TEX_SHADER_QMAP);

	// Load Models
	monkeyMT0 = new Model(OBJ_MONKEY_WALK1);
	monkeyMT0->texture = texMonkey;

	player = monkeyMT0;
	player->texture = texMonkey;
	player->rot.y = 180;

	monkeyMT1 = new Model(OBJ_MONKEY_WALK1, MODEL_TYPE_VTN, false);
	monkeyMT1->texture = texMonkey;
	monkeyMT1->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT1->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT2 = new Model(OBJ_MONKEY_WALK2, MODEL_TYPE_VTN, false);
	monkeyMT2->texture = texMonkey;
	monkeyMT2->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT2->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT3 = new Model(OBJ_MONKEY_WALK3, MODEL_TYPE_VTN, false);
	monkeyMT3->texture = texMonkey;
	monkeyMT3->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT3->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT4 = new Model(OBJ_MONKEY_WALK4, MODEL_TYPE_VTN, false);
	monkeyMT4->texture = texMonkey;
	monkeyMT4->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT4->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT5 = new Model(OBJ_MONKEY_WALK5, MODEL_TYPE_VTN, false);
	monkeyMT5->texture = texMonkey;
	monkeyMT5->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT5->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT6 = new Model(OBJ_MONKEY_WALK6, MODEL_TYPE_VTN, false);
	monkeyMT6->texture = texMonkey;
	monkeyMT6->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT6->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT7 = new Model(OBJ_MONKEY_WALK7, MODEL_TYPE_VTN, false);
	monkeyMT7->texture = texMonkey;
	monkeyMT7->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT7->originOffsetPos = monkeyMT0->originOffsetPos;

	monkeyMT8 = new Model(OBJ_MONKEY_WALK8, MODEL_TYPE_VTN, false);
	monkeyMT8->texture = texMonkey;
	monkeyMT8->boundingBox = monkeyMT0->boundingBox;
	//monkeyMT8->originOffsetPos = monkeyMT0->originOffsetPos;

	island = new Model(OBJ_LEVEL_ISLAND, MODEL_TYPE_VTN, false);
	island->texture = texIsland;

	testModel = new Model("Resources/Models/bf.obj");
	testModel->texture = texUVHelper;

	floor.push_back(island);

	for (int i = 1; i <= 112; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "palmTree" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texPalmTree;
		obj1->boundingBox = Vec3(0.5, 0.5, 0.5);
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	for (int i = 1; i <= 57; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "sphereTree" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texSphereTree;
		obj1->boundingBox = Vec3(0.5, 0.5, 0.5);
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}


	for (int i = 1; i <= 25; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "coneTree" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texConeTree;
		obj1->boundingBox = Vec3(0.5, 0.5, 0.5);
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	for (int i = 1; i <= 75; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "fence" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texFence;
		obj1->boundingBox = Vec3(0.5, 0.5, 0.5);
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	for (int i = 1; i <= 6; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "barrel" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texBarrel;
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	for (int i = 1; i <= 3; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "sign" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texSign;
		obj1->boundingBox = Vec3(0.5, 0.5, 0.5);
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	//for (int i = 1; i <= 7; i++)
	//{
	//	char buffer [5];
	//	_itoa (i, buffer, 10);
	//	std::string filename = RES_PATH_ISLAND "house" + std::string(buffer) + ".obj";

	//	obj1 = new Model(filename.c_str());
	//	obj1->texture = texUVHelper;
	//	obj1->boundingBox = Vec3(0.5, 0.5, 0.5);
	//	objects.push_back(obj1);
	//	collisionObjects.push_back(obj1);
	//}

	for (int i = 1; i <= 1; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "rockA" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texRockB;
		obj1->boundingBox = obj1->boundingBox * 0.7f;
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	for (int i = 1; i <= 1; i++)
	{
		char buffer [5];
		_itoa (i, buffer, 10);
		std::string filename = RES_PATH_ISLAND "rockB" + std::string(buffer) + ".obj";

		obj1 = new Model(filename.c_str());
		obj1->texture = texRockA;
		obj1->boundingBox = obj1->boundingBox * 0.7f;
		objects.push_back(obj1);
		collisionObjects.push_back(obj1);
	}

	obj1 = new Model(RES_PATH_ISLAND "Dock.obj", MODEL_TYPE_VTN, false);
	obj1->texture = loadTexture(TEX_DOCK);
	objects.push_back(obj1);

	obj1 = new Model(RES_PATH_ISLAND "Boat.obj");
	obj1->texture = loadTexture(TEX_BOAT);
	objects.push_back(obj1);

	obj1 = new Model(RES_PATH_ISLAND "Ocean.obj", MODEL_TYPE_VTN, false);
	obj1->texture = loadTexture(TEX_OCEAN);
	objects.push_back(obj1);

	triggerExit = new Model(OBJ_TRIGGER_EXIT);

	player->pos = spawnPoint;

	// Spawn coconuts along path locations
	pathCoconutTrail = loadPaths(PATH_COCONUT_TRAIL);
	Model* coconut;
	for (unsigned int i = 0; i < pathCoconutTrail.waypoints.size(); i++)
	{
		coconut = new Model(OBJ_POWERUP_COCONUT);
		coconut->texture = texCoconut;
		coconut->pos = pathCoconutTrail.waypoints[i];
		coconut->pos.y += 3.f;
		coconut->scale = Vec3(0.4, 0.4, 0.4);
		powerUps.push_back(coconut);
	}

	// Load falling rocks
	pathRockFall = loadPaths(PATH_ROCK_FALL);
	for (unsigned int i = 0; i < pathRockFall.waypoints.size(); i++)
	{
		int randInt = rand() % 2 + 1;

		obj1 = new Model(OBJ_POWERUP_COCONUT);
		obj1->texture = texMolten;
		obj1->scale = Vec3(2, 2, 2);
		obj1->rot.x = Random (-90, 90);
		obj1->rot.y = Random (-90, 90);
		obj1->rot.z = Random (-90, 90);

		obj1->pos = pathRockFall.waypoints[i];
		fallingRocks.push_back(obj1);

	}

	//Randomize the rock fall using fisher-yates shuffle to ensure no duplicates
	for(int i = pathRockFall.waypoints.size()-1; i > 0; i--)
	{
		int randInt = rand() % i;

		//swap
		Vec3 temp = fallingRocks[randInt]->pos;
		fallingRocks[randInt]->pos = fallingRocks[i]->pos;
		fallingRocks[i]->pos = temp;
	}

	hud = new HUD(&window, 1, 120000, 0 );
	GameSmithsMenuManager::CreateMenus(&window);

	// Load sounds
	soundBump.initialize();
	soundBump1.initialize();
	soundBump2.initialize();
	soundPowerUp.initialize();
	soundFall.initialize();
	soundExplosion.initialize();
	soundMenuOpen.initialize();
	soundMenuClick.initialize();
	soundBegin.initialize();
	soundTryAgain.initialize();
	soundFinish.initialize();
	soundHurryUp.initialize();
	music1.initialize();

	soundBump.load(SOUND_BUMP);
	soundBump1.load(SOUND_BUMP1);
	soundBump2.load(SOUND_BUMP2);
	soundPowerUp.load(SOUND_POWERUP2);
	soundFall.load(SOUND_FALL);
	soundExplosion.load(SOUND_EXPLOSION);
	soundMenuOpen.load(SOUND_MENU_OPEN);
	soundMenuClick.load(SOUND_MENU_CLICK);
	soundBegin.load(SOUND_BEGIN);
	soundTryAgain.load(SOUND_TRY_AGAIN);
	soundFinish.load(SOUND_FINISH);
	soundHurryUp.load(SOUND_HURRY);
	srand(time(NULL));
	int randInt = rand() % 3 + 1;

	if (randInt == 1)
		music1.load(MUSIC_G8);
	else if (randInt == 2)
		music1.load(MUSIC_AGB);
	else if (randInt == 3)
		music1.load(MUSIC_SAAB);

	//music1.setVolume(10);
	//music1.channel->setVolume(0.5);
	music1.setLoop(true);

	pathCameraIntro = loadPaths(PATH_CAMERA_INTRO);

	monkeyAnimation = 1;
	isAnimating = false;

	nextAnimation();


	// For Shaders
	fsqPlane->Initialize(6, 0, 1);

	const float vertex[18] = {
		-1.0f, -1.0f, -1.0f, 
		1.0f, -1.0f, -1.0f, 
		-1.0f,  1.0f, -1.0f, 
		-1.0f,  1.0f, -1.0f, 
		1.0f, -1.0f, -1.0f, 
		1.0f,  1.0f, -1.0f, 
	};
	const float texcoord[12] = {
		0.0f, 0.0f, 
		1.0f, 0.0f, 
		0.0f, 1.0f, 
		0.0f, 1.0f, 
		1.0f, 0.0f, 
		1.0f, 1.0f, 
	};
	fsqPlane->AddVertices(vertex);
	fsqPlane->AddTexcoords(texcoord);

	boxBlurShader = new cbmini::cbfw::GLSLProgram;
	gaussBlur2DShader = new cbmini::cbfw::GLSLProgram;
	gaussBlurXShader = new cbmini::cbfw::GLSLProgram;
	gaussBlurYShader = new cbmini::cbfw::GLSLProgram;

	brightToneShader = new cbmini::cbfw::GLSLProgram;
	additiveShader = new cbmini::cbfw::GLSLProgram;

	celShader = new cbmini::cbfw::GLSLProgram;
	postOutlines = new cbmini::cbfw::GLSLProgram;
	passThroughShader = new cbmini::cbfw::GLSLProgram;
	motionBlendShader = new cbmini::cbfw::GLSLProgram;
	motionBlurShader = new cbmini::cbfw::GLSLProgram;
	particleShader = new cbmini::cbfw::GLSLProgram;
	particleCompositeShader = new cbmini::cbfw::GLSLProgram;

	CreateMotionBlurShaderProgram(motionBlurShader);
	CreateBlendShaderProgram(motionBlendShader);
	CreateAdditiveShaderProgram(additiveShader);
	CreateBrightToneShaderProgram(brightToneShader);
	CreateBoxBlurProgram(boxBlurShader);
	CreateGaussBlur2DProgram(gaussBlur2DShader);
	CreateGaussBlurXProgram(gaussBlurXShader);
	CreateGaussBlurYProgram(gaussBlurYShader);
	CreateCelShaderProgram(celShader);
	CreateOutlinesProgram(postOutlines);
	CreatePassthroughShaderProgram(passThroughShader);
	CreateParticleShaderProgram(particleShader);
	CreateParticleCompositeProgram(particleCompositeShader);
	curShader = boxBlurShader;

	sceneFBO->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1, 0);
	outlinesFBO->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1, 0);
	particleFBO->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1, 0);
	blurFBO1->Initialize(WINDOW_WIDTH/BLUR_DOWNSAMPLE, WINDOW_HEIGHT/BLUR_DOWNSAMPLE, 1, 0);
	blurFBO2->Initialize(WINDOW_WIDTH/BLUR_DOWNSAMPLE, WINDOW_HEIGHT/BLUR_DOWNSAMPLE, 1, 0);
	brightFBO->Initialize(WINDOW_WIDTH/BLUR_DOWNSAMPLE, WINDOW_HEIGHT/BLUR_DOWNSAMPLE, 1, 0);
	motionBlurFBO->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1, 0);

	// Particles
	particleSystem = new ParticleEruption;
	particleSystem->Initialize(texPartSmoke, 200, 15, 5, 0, Vec3(57, 250, 26), Vec3(0, 100, 0), Vec3(0, -10, 0));
	particleSystem->Start();
	environParticles.push_back(particleSystem);

	particleSystem = new ParticleExplosion;
	particleSystem->Initialize(texPartFire, 100, 2.5, 5, 0, Vec3(57, 300, 26), Vec3(50, 25, 50), Vec3(0, -10, 0));
	particleSystem->Start();
	environParticles.push_back(particleSystem);

	particleSystem = new ParticleAsh;
	particleSystem->Initialize(texPartFire, 2000, 1, 5, 0, Vec3(0.0, 200.0, 0.0), Vec3(50, 50, 50), Vec3(0, -10, 0));
	particleSystem->Start();
	environParticles.push_back(particleSystem);
}

void Game::processEvents()
{
	float joystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float joystickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	//printf("%f\n", joystickX);
	//printf("%f\n", joystickY);
	//for (int i = 0; i < 8; i++)
	//{
	//	if (sf::Joystick::isConnected(0))
	//	{
	//		bool isConnected = true;
	//	}
	//}

	window.setMouseCursorVisible(SFML_CURSOR_VISIBLE);

	Vec3 oldPos = player->pos;
	
	// Forward / Back
	player->pos +=player->forward*velocity.z;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.z += acceleration;
	}
	else if (sf::Joystick::isButtonPressed(0, 0))
	{
		velocity.z = MAXSPEED;
	}
	else if (joystickY < -25)
	{
		float amount = joystickY/-100.f;
		velocity.z += acceleration * amount;

		maxSpeed = MAXSPEED * amount;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.z -= acceleration;
	}
	else if (sf::Joystick::isButtonPressed(0, 2))
	{
		velocity.z = -MAXSPEED;
	}
	else if (joystickY > 25)
	{
		float amount = joystickY/100;
		velocity.z -= acceleration * amount;

		maxSpeed = MAXSPEED * amount;
	}
	else
	{
		velocity.z = velocity.z*0.95f;
	}
	if (velocity.z > maxSpeed) velocity.z = maxSpeed;
	if (velocity.z < -maxSpeed/3) velocity.z = -maxSpeed/3;

	// Strafing
	player->pos +=player->strafe*velocity.x;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::isButtonPressed(0, 6))
	{
		velocity.x -= acceleration*2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, 7))
	{
		velocity.x += acceleration*2;
	}
	else
	{
		velocity.x = velocity.x*0.5f;
	}
	if (velocity.x > maxSpeed/2) velocity.x = maxSpeed/2;
	if (velocity.x < -maxSpeed/2) velocity.x = -maxSpeed/2;

	static int curJumpTime = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 11)) //jumping
	{
		curJumpTime++;

		if (canJump && curJumpTime < jumpTime)
		{
			velocity.y += 6*acceleration;
		}
		else
		{
			canJump = false;
		}
	}

	// Gravity
	velocity.y -= acceleration*2;
	
	player->pos += player->up*velocity.y;

	// Check if player is within boundaries of island
	unsigned int i;
	bool groundDetected = false;
	Vec3 v1, v2, v3;
	for (i = 0; i < island->vertices.size() && !groundDetected; i+=9)
	{
		v1 = Vec3 (island->vertices[i], island->vertices[i+1], island->vertices[i+2]);
		v2 = Vec3 (island->vertices[i+3], island->vertices[i+4], island->vertices[i+5]);
		v3 = Vec3 (island->vertices[i+6], island->vertices[i+7], island->vertices[i+8]);

		Vec3 origin (player->pos.x, player->pos.y+100.f, player->pos.z);
		Vec3 destination (0.0, -1.0, 0.0);

		groundDetected = rayTriangleIntersection(v1, v2, v3, origin, destination);
	}

	// Make sure player is above the terrain
	if (groundDetected)
	{
		// Use barycentric interpolation on intersected triangle to determine the y value
		Vec3 p1 (v1.x, 0.0, v1.z);
		Vec3 p2 (v2.x, 0.0, v2.z);
		Vec3 p3 (v3.x, 0.0, v3.z);
		Vec3 playerPos (player->pos.x, 0.0, player->pos.z);

		Vec3 f1 = p1 - playerPos;
		Vec3 f2 = p2 - playerPos;
		Vec3 f3 = p3 - playerPos;

		float totalArea = (p1-p2).Cross(p1-p3).GetLength();
		float a1 = f2.Cross(f3).GetLength()/totalArea;
		float a2 = f3.Cross(f1).GetLength()/totalArea;
		float a3 = f1.Cross(f2).GetLength()/totalArea;

		float curY = (v1.y * a1) + (v2.y * a2) + (v3.y * a3);
		curY += PLAYER_GROUND_OFFSET;

		// player is below terrain
		if (velocity.y < 0 && player->pos.y < curY)
		{
			velocity.y = 0;

			player->pos.y = curY;

			// spawn particles if running at full speed
			if (velocity.GetLength() >= maxSpeed)
			{
				ParticleSystem* tempParticle = new ParticleImpactCloud;
				tempParticle->Initialize(texPart, 1, 2, 2, 1, player->pos-(player->forward*5), Vec3(50, 25, 50), Vec3(0, 5, 0));
				tempParticle->blendSource = GL_SRC_ALPHA;
				tempParticle->blendDest = GL_ONE;
				tempParticle->Start();
				tempParticles.push_back(tempParticle);
			}

			// spawn particles when landing from jump
			if (curJumpTime != 0)
			{
				ParticleSystem* tempParticle = new ParticleImpactCloud;
				tempParticle->Initialize(texPart, 10, 2, 3, 1, player->pos, Vec3(100, 50, 100), Vec3(0, 10, 0));
				tempParticle->blendSource = GL_SRC_ALPHA;
				tempParticle->blendDest = GL_ONE;
				tempParticle->Start();

				tempParticles.push_back(tempParticle);
			}

			canJump = true;
			curJumpTime = 0;
		}

		fallingSoundPlaying = false;
	}
	else if (!fallingSoundPlaying)
	{
		soundTryAgain.playDawg();
		soundFall.playDawg();
		
		fallingSoundPlaying = true;
	}

	// Camera orientation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->azemuth -= 1.f*PLAYER_SPEED;
		cam->azemuth -= 1.f*PLAYER_SPEED;
	}
	else if (joystickX < -25)
	{
		player->azemuth -= .5f*PLAYER_SPEED;
		cam->azemuth -= .5f*PLAYER_SPEED;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->azemuth += 1.f*PLAYER_SPEED;
		cam->azemuth += 1.f*PLAYER_SPEED;
	}
	else if (joystickX > 25)
	{
		player->azemuth += .5f*PLAYER_SPEED;
		cam->azemuth += .5f*PLAYER_SPEED;
	}

	hasCollided = false;
	// Collision with environment
	for (unsigned int i = 0; i < collisionObjects.size(); i++)
	{
		if (detectColiding (player, collisionObjects[i]))
		{
			if (!collisionSoundPlaying)
			{
				collisionSoundPlaying = true;
				//Beep(523, 500);

				if (velocity.z > maxSpeed/2 || velocity.z < -maxSpeed/2)
				{
					soundBump1.playDawg();

				}
				else
				{
					soundBump2.playDawg();
				}
				soundBump.playDawg();
			}

			hasCollided = true;
			velocity.z *= -0.25;
			velocity.x *= -0.25;
			player->pos.z = oldPos.z;
			player->pos.x = oldPos.x;
			break;
		}
	}

	if (!hasCollided && collisionSoundPlaying)
	{
		collisionSoundPlaying = false;
	}

	// Collision with powerups
	for (unsigned int i = 0; i < powerUps.size(); i++)
	{
		if (detectColiding (player, powerUps[i]))
		{
			ParticleSystem* tempParticle = new ParticleEruption;
			tempParticle->Initialize(texPartScore1000, 1, 2, 1, 1, Vec3(powerUps[i]->pos), Vec3(0, 50, 0), Vec3(0, -10, 0));
			tempParticle->Start();
			tempParticles.push_back(tempParticle);

			powerUps.erase(powerUps.begin() + i);
			score += 1000;
			soundPowerUp.playDawg();
			break;
		}
	}

	// Exit reached, spawn particles around player
	if (detectColiding (player, triggerExit))
	{
		if (!levelComplete)
		{
			score += hud->getTimeLeft() * 500;
			soundFinish.playDawg();
		}

		levelComplete = true;
	}

///////////////////////////////////////////////////////////////////////////////
	while (window.pollEvent(event))
	{
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1))
		{
			soundMenuOpen.playDawg();
		}

		// Close window : exit
		if (event.type == sf::Event::Closed)
			window.close();

		// Escape key : exit
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			window.close();

		// Example05 - toggle wireframe mode ON/OFF
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::K)) {
			if (polyMode == GL_FILL)
				polyMode = GL_LINE; 
			else polyMode = GL_FILL;

			glPolygonMode( GL_FRONT_AND_BACK, polyMode );
		}

		// Resize event : adjust viewport
		if (event.type == sf::Event::Resized) {
			glViewport(0, 0, event.size.width, event.size.height);
		}

		// Toggle Camera
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tilde)) 
		{
			cameraType = !cameraType;
		}

		// Toggle Music
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::M)) 
		{
			musicOn = !musicOn;

			if (musicOn)
			{
				;
				music1.playDawg();
			}
			else
				music1.channel->stop();
				//music1.stop();
		}

		// Test 3D sound
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::J)) 
		{
			//printf("%f, %f, %f\n", player->pos.x, player->pos.y, player->pos.z);

			FMOD_VECTOR curPlayerPos;
			curPlayerPos.x = player->pos.x;
			curPlayerPos.y = player->pos.y;
			curPlayerPos.z = player->pos.z;

			soundExplosion.playDawg();
			soundExplosion.channel->setVolume(1);
			soundExplosion.listenerpos = curPlayerPos;
			soundExplosion.updatelocation(57, 250, 26);
			soundExplosion.update();
		}

		// Toggle Motion Blur
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num0)) 
		{
			blurOn = !blurOn;
		}
	}

	// Mouse control
	sf::Vector2i center;
	center = sf::Vector2i(window.getSize().x/2 +window.getPosition().x, 
		window.getSize().y/2+window.getPosition().y);

	sf::Vector2i mousePos;
	mousePos = sf::Vector2i(mouse.getPosition().x, 
		mouse.getPosition().y);

	sf::Vector2i diff = mousePos-center;

	mouse.setPosition(sf::Vector2i(window.getSize().x/2 +window.getPosition().x, 
		window.getSize().y/2+window.getPosition().y));

	camOffsetAzumuth += float(diff.x)*0.1f;
	camOffsetElevation += float(diff.y)*0.1f;

	if (cameraType == THIRD_PERSON)
	{
		if (camOffsetAzumuth > 5) 
		{
			camOffsetAzumuth = 5; //right
			player->azemuth += .5f*camOffsetAzumuth;
		}
		else if (camOffsetAzumuth< -5)
		{
			camOffsetAzumuth = -5; //left
			player->azemuth += .5f*camOffsetAzumuth;
		}

		if (camOffsetElevation < -90)
		{
			camOffsetElevation = -90; //up
		}
		else if (camOffsetElevation > 45)
		{
			camOffsetElevation = 45; //down
		}
	}
	else if (cameraType == FIRST_PERSON)
	{
		if (camOffsetAzumuth > 5) 
		{
			camOffsetAzumuth = 5; //right
			player->azemuth += .9f*camOffsetAzumuth;
		}
		else if (camOffsetAzumuth< -5)
		{
			camOffsetAzumuth = -5; //left
			player->azemuth += .9f*camOffsetAzumuth;
		}

		if (camOffsetElevation < -90)
		{
			camOffsetElevation = -90; //up
		}
		else if (camOffsetElevation > 45)
		{
			camOffsetElevation = 45; //down
		}
	}

	cam->azemuth = player->azemuth + camOffsetAzumuth;
	cam->elevation = player->elevation + camOffsetElevation;

	window.setActive();

	// Update falling rocks
	for (int i = 0; i < spawnedFallingRocks.size(); i++)
	{
		if (!spawnedFallingRocksGrounded[i])
		{
			spawnedFallingRocksVelocity[i] += 2*acceleration;

			spawnedFallingRocks[i]->pos.y -= spawnedFallingRocksVelocity[i];

			// rock landed
			if (spawnedFallingRocks[i]->pos.y <= spawnedFallingRocksDest[i].y)
			{
				spawnedFallingRocks[i]->pos.y = spawnedFallingRocksDest[i].y;
				spawnedFallingRocksGrounded[i] = true;

				// if rock collides with player on landing, player death
				if (detectColiding(player, spawnedFallingRocks[i]))
				{
					soundTryAgain.playDawg();
					player->pos = spawnPoint;
					score -= 2000.f;
				}

				collisionObjects.push_back(spawnedFallingRocks[i]);

				// Spawn particles when rock hits terrain
				ParticleSystem* tempParticle = new ParticleImpactCloud;
				tempParticle->Initialize(texPartSmoke, 40, 4, 3, 1, spawnedFallingRocks[i]->pos, Vec3(200, 100, 200), Vec3(0, 20, 0));
				//tempParticle->blendSource = GL_SRC_ALPHA;
				//tempParticle->blendDest = GL_ONE;
				tempParticle->Start();

				tempParticles.push_back(tempParticle);
			}
		}
	}

	if (hud->getTimeLeft() <= 30 && !hurryUpPlayed)
	{
		music1.channel->stop();
		music1.load(MUSIC_MEAG);
		music1.playDawg();

		hurryUpPlayed = true;
		soundHurryUp.playDawg();
	}
}

void Game::update()
{
	if (player->pos.y < -200.f)
	{
		score -= 5000;
		player->pos = spawnPoint;
	}

	static float t;
	static bool lerpForward = true;
	
	float secondsPassed = clock.getElapsedTime().asSeconds();

	if (particleSystem->IsSystemAlive())
		particleSystem->Update(secondsPassed, cam->pos);
	else
	{
		;
		//printf("Particle System over");
	}
	

	for (unsigned int i = 0; i < environParticles.size(); i++)
	{
		environParticles[i]->Update(secondsPassed, cam->pos);
	}
	for (unsigned int i = 0; i < tempParticles.size(); i++)
	{
		tempParticles[i]->Update(secondsPassed, cam->pos);
	}
	tempParticles.erase(std::remove_if(tempParticles.begin(), tempParticles.end(), [](ParticleSystem* i) { return !i->IsSystemAlive();}), tempParticles.end());

	//printf("%d", tempParticles.size());
	if (isPlayingIntro)
	{
		if (path.currentWaypointIndex == path.waypoints.size()-1)
		{
			stopIntro();
		}

		path.Update(secondsPassed);

	}

	if (isAnimating)
	{
		t += abs(velocity.z*MORPH_WALK_SPEED)*secondsPassed;

		if (t > 1.f)
		{
			t = 0;
			//isAnimating = false;

			player = target;

			nextAnimation();
		}
		else 
		{
			delete result;
			result = player->morph(target, t);

		}
	}

	clock.restart();

	glEnable(GL_LIGHTING);

	hud->setScore(score);
	hud->update(false);
	player->update();

	if (cameraType == THIRD_PERSON)
	{
		cam->pos = result->pos - result->forward*CAMERA_THIRD_PERSON_OFFSET;
		cam->pos.y = result->pos.y+CAMERA_THIRD_PERSON_Y_OFFSET;

		cam->azemuth = result->azemuth + camOffsetAzumuth;
		cam->elevation = result->elevation + camOffsetElevation;
	}
	else if (cameraType == FIRST_PERSON)
	{
		cam->pos = player->pos + player->forward*CAMERA_FIRST_PERSON_OFFSET;
		cam->pos.y = player->pos.y+7.f;
	}

	//sky.pos = cam->pos;

	static float rf_t;
	static int rf_i = 0;

	rf_t += secondsPassed;

	if (rf_t > 1.f)
	{
		if (rf_i < fallingRocks.size())
		{
			spawnedFallingRocksDest.push_back(fallingRocks[rf_i]->pos);
			fallingRocks[rf_i]->pos.y += 1000.f;
			spawnedFallingRocks.push_back(fallingRocks[rf_i]);
			spawnedFallingRocksGrounded.push_back(false);
			spawnedFallingRocksVelocity.push_back(0.0);
			rf_i++;

			rf_t = 0;
		}
	}

	if (hud->getTimeLeft() == 0)
	{
		reset();
	}
}

void Game::draw()
{
	updateAllAnimations();

	// PASS 1 - Render Scene
	sceneFBO->Activate();
		glPolygonMode( GL_FRONT_AND_BACK, polyMode );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		celShader->Activate();
			sceneFBO->SetTextureInput(1);
			glBindTexture(GL_TEXTURE_2D, texQMap);

			cam->Activate();

			const bmath::mat::mat3 cameraRotation = bmath::mat::makeRotationEuler3XYZ(0.0, deg2radf*(-1*cam->azemuth), 0.0);
			eyeToWorld = bmath::mat::makeTransform(cameraRotation, toBMathVec3f(cam->pos));

			//for screen space motion blur
			prevViewProjectionMat = viewProjectionMat;

			UpdateCameraMatrices();

			const bmath::vec::vec4 lightPosWorld(spawnPoint.x, spawnPoint.y + 100.f, spawnPoint.z, 1);
			const bmath::vec::vec4 eyePosWorld(toBMathVec3f(cam->pos));
			
			//Draw player
			if (!isPlayingIntro && cameraType != FIRST_PERSON)
			{
				if (isAnimating)
				{
					sceneFBO->SetTextureInput(0);
					glBindTexture(GL_TEXTURE_2D, result->texture);
					SetupAndDraw(result, lightPosWorld, eyePosWorld);
				}
				else
				{
					sceneFBO->SetTextureInput(0);
					glBindTexture(GL_TEXTURE_2D, player->texture);
					SetupAndDraw(player, lightPosWorld, eyePosWorld);
				}
			}
	
			//Draw Floor
			for (unsigned int i = 0; i < floor.size(); i++)
			{
				sceneFBO->SetTextureInput(0);
				glBindTexture(GL_TEXTURE_2D, floor[i]->texture);
				SetupAndDraw(floor[i], lightPosWorld, eyePosWorld);
			}

			//Draw all other objects
			for (unsigned int i = 0; i < objects.size(); i++)
			{
				sceneFBO->SetTextureInput(0);
				glBindTexture(GL_TEXTURE_2D, objects[i]->texture);
				SetupAndDraw(objects[i], lightPosWorld, eyePosWorld);
			}
			
			//Draw temp powerups
			for (unsigned int i = 0; i < powerUps.size(); i++)
			{
				sceneFBO->SetTextureInput(0);
				glBindTexture(GL_TEXTURE_2D, powerUps[i]->texture);
				SetupAndDraw(powerUps[i], lightPosWorld, eyePosWorld);
			}

			//Draw falling rocks
			for (unsigned int i = 0; i < spawnedFallingRocks.size(); i++)
			{
				sceneFBO->SetTextureInput(0);
				glBindTexture(GL_TEXTURE_2D, spawnedFallingRocks[i]->texture);
				SetupAndDraw(spawnedFallingRocks[i], lightPosWorld, eyePosWorld);
			}

		celShader->Deactivate();

		particleShader->Activate();
			sceneFBO->SetTextureInput(0);

			for (unsigned int i = 0; i < environParticles.size(); i++)
			{
				environParticles[i]->Draw(viewMat, projectionMat, pModelView, pProj, pSize);
			}
			for (unsigned int i = 0; i < tempParticles.size(); i++)
			{
				tempParticles[i]->Draw(viewMat, projectionMat, pModelView, pProj, pSize);
			}

		particleShader->Deactivate();

	sceneFBO->Deactivate();

	if (blurOn)
		motionBlurFBO->Activate();

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	fsqPlane->Activate();

		glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
		glDisable(GL_DEPTH_TEST);

		postOutlines->Activate();

		sceneFBO->SetTextureInput(0);
		sceneFBO->BindColour(0);
		sceneFBO->SetTextureInput(1);
		sceneFBO->BindColour(1);
		sceneFBO->SetTextureInput(2);
		sceneFBO->BindDepth();

		fsqPlane->ActivateAndRender();

		sceneFBO->SetTextureInput(2);
		sceneFBO->UnbindTextures();
		sceneFBO->SetTextureInput(1);
		sceneFBO->UnbindTextures();
		sceneFBO->SetTextureInput(0);
		sceneFBO->UnbindTextures();

		postOutlines->Deactivate();
	//outlinesFBO->Deactivate();
		
	if (blurOn)
	{
		motionBlurFBO->Deactivate();
		
		motionBlurShader->Activate();

		glUniformMatrix4fv(mbInvVP, 1, 0, eyeToWorld.m);
		glUniformMatrix4fv(mbPrevVP, 1, 0, prevViewProjectionMat.m);

		motionBlurFBO->SetTextureInput(0);
		motionBlurFBO->BindColour(0);
		sceneFBO->SetTextureInput(1);
		sceneFBO->BindDepth();

		fsqPlane->ActivateAndRender();

		sceneFBO->SetTextureInput(1);
		sceneFBO->UnbindTextures();
		motionBlurFBO->SetTextureInput(0);
		motionBlurFBO->UnbindTextures();

		motionBlurShader->Deactivate();
	}

	cbmini::cbfw::GLSLProgram::Deactivate();
	cbmini::cbfw::FrameBuffer::Deactivate();
	cbmini::cbfw::VertexBuffer::Deactivate();

	drawGUI();
}

void Game::drawGUI()
{
	glPolygonMode( GL_FRONT_AND_BACK, polyMode );

	hud->display();
	GameSmithsMenuManager::DisplayMenus();

	if (GameSmithsMenuManager::getGameState() == GameSmithsMenuManager::HELP)
	{
		HelpMe help(&window);
		help.displayHelp(HelpMe::HELP);
	}
	else if (GameSmithsMenuManager::getGameState() == GameSmithsMenuManager::TUTORIAL)
	{
		HelpMe help(&window);
		help.displayHelp(HelpMe::TUTORIAL);
	}
	else if (GameSmithsMenuManager::getGameState() == GameSmithsMenuManager::START)
	{
		//HelpMe help(&window);
		//help.displayHelp(HelpMe::TUTORIAL);
		;
	}
	else if (GameSmithsMenuManager::getGameState() == GameSmithsMenuManager::NEW_GAME)
	{
		//HelpMe help(&window);
		//help.displayHelp(HelpMe::TUTORIAL);
		reset();
		GameSmithsMenuManager::setGameState(GameSmithsMenuManager::RUN);
	}
	else if (GameSmithsMenuManager::getGameState() == GameSmithsMenuManager::EXIT)
	{
		window.close();
	}

}

void Game::reset()
{
	levelComplete = false;
	hurryUpPlayed = false;

	delete hud;
	hud = new HUD(&window, 1, 120000, 0 );
	score = 0;
	hud->setScore(0);
	player->pos = spawnPoint;

	soundBegin.playDawg();
}

// intro camera sequence
void Game::playIntro()
{
	isPlayingIntro = !isPlayingIntro;

	int index = 0;
	path.Stop();
	path.RemoveAllWaypoints();
	path.Reset();

	path.AddWaypointToEnd(player->pos);

	Vec3 destNode = pathCameraIntro.waypoints[0];
	Vec3 directionDest = destNode - player->pos;
	directionDest = directionDest * .1f;

	for (unsigned int i = 1; i < 10 ; i++)
	{
		Vec3 tempDestPath = player->pos + (directionDest*i);
		path.AddWaypointToEnd(tempDestPath);
	}

	for (unsigned int i = 0; i < pathCameraIntro.waypoints.size(); i++)
	{
		path.AddWaypointToEnd(pathCameraIntro.waypoints[i]);
	}

	path.SetTotalTime(INTRO_SCENE_DURATION);
	path.SetCycling(false);
	path.SetLooping(false);
	path.Start();
}

void Game::stopIntro()
{
	isPlayingIntro = false;

	path.Stop();

	player->pos = spawnPoint;
}

// compute a transform (obj-to-world) using a 'look-at' utility
// this can be used for anything, not just a camera!
const bmath::mat::mat4 Game::ObjectLookAt(Object *obj, 
	const bmath::vec::vec3 position, 
	const bmath::vec::vec3 worldUp, 
	const bmath::vec::vec3 focalPoint)
{
	//	
	//	YOU SHOULD REMEMBER THIS FROM LAST TERM: 
	//	"FRENET FRAME"
	//
	//				c1 = j = Up
	//						o
	//						|	
	//						|  . (Dir)
	//						| .
	//						|.
	//	c3 = E = position	X----------o  c0 = i = Right
	//					   /
	//					  /
	//					 o
	//	c2 = k = -(Direction)
	//	

	bmath::mat::mat4 ret;

	// set position
	ret.c3.xyz = position;
	obj->pos = toVec3f(position);

	// set direction
	ret.c2.xyz = bmath::util::normalize(position - focalPoint);

	// set right
	ret.c0.xyz = bmath::vec::crossNormalize(worldUp, ret.c2.xyz);

	// set up
	ret.c1.xyz = bmath::vec::crossNormalize(ret.c2.xyz, ret.c0.xyz);

	// done
	return ret;
}

const bmath::mat::mat4 Game::ObjectLookAt(Object *obj, 
	const float positionX, const float positionY, const float positionZ, 
	const float worldUpX, const float worldUpY, const float worldUpZ, 
	const float focalPointX, const float focalPointY, const float focalPointZ)
{
	const bmath::vec::vec3 position(positionX, positionY, positionZ);
	const bmath::vec::vec3 worldUp(worldUpX, worldUpY, worldUpZ);
	const bmath::vec::vec3 focalPoint(focalPointX, focalPointY, focalPointZ);
	return ObjectLookAt(obj, position, worldUp, focalPoint);
}


// update the camera-related matrices (one time per frame)
void Game::UpdateCameraMatrices()
{
	// update the stuff that only changes once per frame
	// i.e. anything that has to do with the camera

	// compute V matrix by inverting the camera's 
	//	transform in world space
	viewMat = bmath::mat::transformInverseNoScale(eyeToWorld);

	// then compute the view-projection matrix
	// any model matrix multiplied by this will give us 
	//	the MVP matrix
	viewProjectionMat = projectionMat * viewMat;
}

// update the object-related matrices (per-object rendered)
void Game::UpdateObjectMatrices(const Object *obj)
{
	bmath::mat::mat3 r = (
		makeRotationX3(deg2radf*obj->rot.x) *
		makeRotationY3(deg2radf*obj->rot.y) *
		makeRotationZ3(deg2radf*obj->rot.z) *
		//makeRotationX3(deg2radf*(-1*obj->elevation)) *
		makeRotationY3(deg2radf*(-1*obj->azemuth)));

	const bmath::vec::vec3 t = toBMathVec3f(obj->pos);
	const float s = obj->scale.x;
	//const float s = 1.0;
	modelMat = bmath::mat::makeTransform(r, s, t);

	// compute model-view matrix
	modelViewMat = viewMat * modelMat;

	// compute model-view-projection matrix
	modelViewProjectionMat = projectionMat * modelViewMat;

	// compute object-space matrix
	worldToObject = bmath::mat::transformInverseUniformScale(modelMat);
}

void Game::nextAnimation()
{
	isAnimating = true;

	monkeyAnimation++;

	if (monkeyAnimation > 8)
		monkeyAnimation = 1;

	if (monkeyAnimation == 0)
	{
		target = monkeyMT0;
	}
	else if (monkeyAnimation == 1)
	{
		target = monkeyMT1;
	}
	else if (monkeyAnimation == 2)
	{
		target = monkeyMT2;
	}
	else if (monkeyAnimation == 3)
	{
		target = monkeyMT3;
	}
	else if (monkeyAnimation == 4)
	{
		target = monkeyMT4;
	}
	else if (monkeyAnimation == 5)
	{
		target = monkeyMT5;
	}
	else if (monkeyAnimation == 6)
	{
		target = monkeyMT6;
	}
	else if (monkeyAnimation == 7)
	{
		target = monkeyMT7;
	}
	else if (monkeyAnimation == 8)
	{
		target = monkeyMT8;
	}
	//result = player->morph(target, 0.f);
}

void Game::updateAllAnimations()
{
	monkeyMT1->copyAllAttributes(player);
	monkeyMT2->copyAllAttributes(player);
	monkeyMT3->copyAllAttributes(player);
	monkeyMT4->copyAllAttributes(player);
	monkeyMT5->copyAllAttributes(player);
	monkeyMT6->copyAllAttributes(player);
	monkeyMT7->copyAllAttributes(player);
	monkeyMT8->copyAllAttributes(player);
}

void Game::SetupAndDraw( Object *obj, bmath::vec::vec4 lightPosWorld, bmath::vec::vec4 eyePosWorld )
{
	bmath::vec::vec4 lightPosObj, eyePosObj;

	UpdateObjectMatrices(obj);
	glUniformMatrix4fv(csMVP, 1, 0, modelViewProjectionMat.m);
	lightPosObj = worldToObject * lightPosWorld;
	eyePosObj = worldToObject * eyePosWorld;
	glUniform3fv(csLightPos, 1, lightPosObj.v);
	glUniform3fv(csEyePos, 1, eyePosObj.v);

	obj->draw();
}
