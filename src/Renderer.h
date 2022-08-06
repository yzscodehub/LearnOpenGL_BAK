#pragma once

#include <GL/glew.h>
#include <cassert>

#define ASSERT(X) if(!(X)) assert(false)

#define GLCall(X)   GLClearError(); \
                    X;              \
                    ASSERT(GLCheckError());

void GLClearError();

bool GLCheckError();