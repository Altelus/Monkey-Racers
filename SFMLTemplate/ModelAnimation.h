#ifndef _MODEL_ANIMATION_H
#define _MODEL_ANIMATION_H

class ModelAnimation : Object
{
public:
	ModelAnimation(const char*, int);

private:
	std::vector <Model> morphTargets;


};

#endif