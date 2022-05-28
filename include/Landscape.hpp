#pragma once

#include <windows.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

class Landscape : public SceneObject
{
	public:
        Landscape(float initialDistance = 0.0f);
        ~Landscape();

  protected:
        virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
        float width;
        float length;
        float distance;
        float rise_;

        std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
        // normal array.
        // texture coord array
};

