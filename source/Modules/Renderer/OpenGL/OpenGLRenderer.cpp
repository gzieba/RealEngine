#include "OpenGLRenderer.h"
#include <glad/glad.h>
#include <cassert>

#include "Common/logging.h"

OpenGLRenderer::OpenGLRenderer()
{
	if(!gladLoadGL())
	{
		LOG(FATAL) << LOCATION << "Failed to initialize GLAD";
	}

	LOG(INFO) << LOCATION << "OpenGLRenderer initialized";
}
