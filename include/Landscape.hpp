#pragma once

#include <windows.h>
#include "SceneObject.hpp"

#include "../../glm-master/glm/glm.hpp"

#include "ColSphereBody.hpp"

class Landscape : public SceneObject
{
	public:
        Landscape(float initialDistance = 0.0f, int repeats = 3);
        ~Landscape();

        bool detectCollision(const ColSphereBody& target) const;
        float getHeightY(const ColSphereBody& target) const;

        void setSpeedZ(float speed);

  protected:
        virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
        bool loadTextures();

        float width;
        float length;
        float distance;
        float rise_;

        std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
        // normal array.
        std::vector< glm::vec3 > normalArray_;
        // texture coord array
        std::vector< glm::vec2 > texCoordArray_;

        GLuint texName_;

        bool texLoaded_;

        int repeats_;
        float speed_ = 0.0f;
};

