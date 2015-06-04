//SFML Includes
#include <GL/glew.h>
#include "Include/SFML/Graphics.hpp"
#include "Include/SFML/OpenGL.hpp"
#include "glext.h"
//#include "Include/SFML/Audio.hpp"
#include <SFML/Audio.hpp>

//Other Useful Includes
#include <math.h>
#include <vector>
#include <list>
#include <stdio.h>

//Constants
#define PI  3.14159265f
#define DTR 0.01745329f
#define RTD 57.2957795f
//Game Engine Classes
#include "CBMiniFW/CBMiniFW.h"
#include "BMath/mat.h"
#include "Vec2.h"
#include "Vec3.h"
#include "AnimationMath.h"
#include "Quaternion.h"
#include "Path.h"
#include "PathNode.h"
#include "HUD.h"

#include "Camera3D.h"
#include "Object.h"
#include "SkyBox.h"
#include "Model.h"
//#include "ParticleEngine.h"
#include "ParticleSystem.h"
#include "ParticleEruption.h"
#include "ParticleExplosion.h"
#include "ParticleImpactCloud.h"
#include "ParticleAsh.h"
#include "sound.h"

#include "Configuration.h"
#include "Utilities.h"
#include "sound.h"
#include "Game.h"
