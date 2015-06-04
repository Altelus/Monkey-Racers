/*
	CB Mini Frame Buffer Object (FBO)
	By Dan Buckstein... and YOU!

	Class that manages an OpenGL Frame Buffer Object (FBO) with colour and 
	depth buffers available.
*/

#ifndef __CBMINI_FW_FRAMEBUFFER_H
#define __CBMINI_FW_FRAMEBUFFER_H


namespace cbmini
{
namespace cbfw
{


class FrameBuffer
{
private: 

	// OpenGL FBO handle
	unsigned int handle;

	// texture handles
	// use an array - you'll see why shortly
	//unsigned int colourTex[1];

	unsigned int colourTex[16];
	unsigned int numTargets;

	// depth target
	unsigned int depthTex;

	// dimensions
	unsigned int width, height;

public: 

	// getters
	// DIY

public: 

	// default ctor
	FrameBuffer();
	
	// dtor
	~FrameBuffer();

	// release buffer from graphics memory
	void Release();

	// initialize frame buffer object
	// returns 1 if successful, 0 if failed
	int Initialize(unsigned int w, unsigned int h, 
		unsigned int colour, bool useDepth=true, 
		bool useHDR=true, bool useLinearFilter=true, bool clamp=true);

	// activate FBO for off-screen rendering
	void Activate() const;

	// deactivate off-screen rendering
	static void Deactivate();

	// bind one of the render target textures
	void BindColour(unsigned int target=0) const;
	void BindDepth() const;

	// deactivate textures
	static void UnbindTextures();

	// switch texture target input (0 - 15)
	static void SetTextureInput(unsigned int texture=0);

};


}
}


#endif	// __CBMINI_FW_FRAMEBUFFER_H