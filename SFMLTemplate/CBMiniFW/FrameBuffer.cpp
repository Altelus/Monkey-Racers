#include "FrameBuffer.h"
using namespace cbmini;
using namespace cbfw;


#include <string.h>
#include "GL/glew.h"


//-----------------------------------------------------------------------------
// frame buffer object class

// ctor and dtor (done)
FrameBuffer::FrameBuffer()
{
	handle = 0;
	memset(colourTex, 0, sizeof(colourTex));
	depthTex = 0;

	width = 0;
	height = 0;

	numTargets = 0;
}

FrameBuffer::~FrameBuffer()
{
	// auto-release
	Release();
}


// release
// IMPLEMENT!
// ******** 
void FrameBuffer::Release()
{
	if (handle)
	{
		// delete FBO
		// **** 
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &handle);

		// delete all textures
		// **** 
		glBindTexture(GL_TEXTURE_2D, 0);
		if (*colourTex)
			glDeleteTextures(1, colourTex);

		// reset values
		handle = 0;
		memset(colourTex, 0, sizeof(colourTex));
		depthTex = 0;
		width = 0;
		height = 0;

		numTargets = 0;
	}
}


// initialization
// IMPLEMENT!
// ******** 
int FrameBuffer::Initialize(unsigned int w, unsigned int h, 
	unsigned int colour, bool useDepth, bool useHDR, 
	bool useLinearFilter, bool clamp)
{
	// validate
	if (w && h && (colour || useDepth))
	{
		// probably a good idea to set a maximum dimension
		const unsigned int maxSize = 4096;
		if (w <= maxSize && h <= maxSize)
		{
			// OpenGL constants for reuse
			// describes properties of the textures that we will create
			const unsigned short filtering = useLinearFilter ? 
				GL_LINEAR : GL_NEAREST;
			const unsigned short wrapping = clamp ? 
				GL_CLAMP_TO_EDGE : GL_REPEAT;
			const unsigned short colourBit = useHDR ? 
				GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;
			const unsigned short colourFormat = useHDR ? 
				GL_RGBA16 : GL_RGBA8;

			// set FBO properties
			width = w;
			height = h;

			// initialize FBO
			// **** 
			glGenFramebuffers(1, &handle);
			glBindFramebuffer(GL_FRAMEBUFFER, handle);

			// if colour is in use, create targets and textures
			// **** 
			/*
			if (colour == 1) //SRT -single render target
			{
				// generate and bind a new empty texture
				// **** 
				glGenTextures(1, colourTex);
				glBindTexture(GL_TEXTURE_2D, *colourTex);
				glTexImage2D(GL_TEXTURE_2D, 0, colourFormat, width, height, 0, GL_RGBA, colourBit, 0);


				// set properties of the texture (filtering and wrapping)
				// what are the differences
				// **** 
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

				// attach it directly to the framebuffer as a target
				// **** 
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *colourTex, 0);
			}
			*/

			if (colour)
			{
				int maxTargets;
				glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxTargets);
				numTargets = (int)colour <= maxTargets ? colour : maxTargets;

				glGenTextures(numTargets, colourTex);

				for (unsigned int i = 0; i < numTargets; ++i)
				{
					glBindTexture(GL_TEXTURE_2D, *(colourTex+i));
					glTexImage2D(GL_TEXTURE_2D, 0, colourFormat, width, height, 0, GL_RGBA, colourBit, 0);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, *(colourTex+i), 0);
				}
			}

			// if depth is to be used, create target and texture
			// **** 
			if(useDepth)
			{
				glGenTextures(1, &depthTex);
				glBindTexture(GL_TEXTURE_2D, depthTex);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
			}

			// check status of buffer
			// **** 
			int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

			if(status == GL_FRAMEBUFFER_COMPLETE)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

				return 1;
			}
			
			// if the buffer creation failed, release
			Release();
		}
	}
	return 0;
}


// activate FBO
// IMPLEMENT!
// ******** 
void FrameBuffer::Activate() const
{
	if (handle)
	{
		// bind FBO
		glBindFramebuffer(GL_FRAMEBUFFER, handle);

		// need to set all targets appropriately
		// **** 
		/*
		if (colourTex)
		{
			GLenum targetName = GL_COLOR_ATTACHMENT0;

			glDrawBuffers(1, &targetName);
		}
		else
 		{
 			glDrawBuffer(GL_NONE);
 		}
		*/
		if (numTargets)
		{
			const GLenum targetName[16] = {
				GL_COLOR_ATTACHMENT0,
				GL_COLOR_ATTACHMENT1,
				GL_COLOR_ATTACHMENT2,
				GL_COLOR_ATTACHMENT3,
				GL_COLOR_ATTACHMENT4,
				GL_COLOR_ATTACHMENT5,
				GL_COLOR_ATTACHMENT6,
				GL_COLOR_ATTACHMENT7,
				GL_COLOR_ATTACHMENT8,
				GL_COLOR_ATTACHMENT9,
				GL_COLOR_ATTACHMENT10,
				GL_COLOR_ATTACHMENT11,
				GL_COLOR_ATTACHMENT12,
				GL_COLOR_ATTACHMENT13,
				GL_COLOR_ATTACHMENT14,
				GL_COLOR_ATTACHMENT15
			};

			glDrawBuffers(numTargets, targetName);
		}
		else
		{
			glDrawBuffer(GL_NONE);
		}

		// if we are using depth, need to enable it
		// **** 
		if(depthTex)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);


	}
}

// deactivate
// IMPLEMENT!
// ******** 
void FrameBuffer::Deactivate()
{
	// disable FBO
	// **** 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// tell OpenGL that we want to render to the back buffer again
	// **** 
	glDrawBuffer(GL_BACK);
	// enable depth testing because the back buffer uses it
	// **** 
	glEnable(GL_DEPTH_TEST);
}


// bind/unbind textures (done)
void FrameBuffer::BindColour(unsigned int target) const
{
	if (target < 16)
	{
		// tmp (SRT)
	//	target = 0;
		//if (*colourTex)	// SRT
		if (numTargets)
			glBindTexture(GL_TEXTURE_2D, *(colourTex+target));
	}
}

void FrameBuffer::BindDepth() const
{
	if (depthTex)
		glBindTexture(GL_TEXTURE_2D, depthTex);
}

void FrameBuffer::UnbindTextures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


// set texture input, i.e. which texture are we using (done)
void FrameBuffer::SetTextureInput(unsigned int texture)
{
	if (texture < 16)
		glActiveTexture(GL_TEXTURE0+texture);
}
