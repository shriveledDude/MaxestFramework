#pragma once


#include "../../../src/essentials/types.h"

#ifdef MAXEST_FRAMEWORK_WINDOWS
    #include <Windows.h>
#endif
#include <GL/gl.h>


using namespace NMaxestFramework::NEssentials;


class COGLTextureRenderer
{
public:
	void Create(int width, int height)
	{
		this->width = width;
		this->height = height;

		glEnable(GL_TEXTURE_2D);

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, nullptr);
	}

	void Render(uint8* data)
	{
		glClearColor(0.25f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glEnd();
	}

public:
	int width, height;
	GLuint textureID;
};
