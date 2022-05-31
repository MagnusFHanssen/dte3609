#pragma once

#include <windows.h>
#include "SceneObject.hpp"

#include "../../glm-master/glm/glm.hpp"

#include "ColSphereBody.hpp"

#include "Shader.hpp"

#include "MyVertex.h"

class Landscape : public SceneObject
{
	public:
        Landscape(std::shared_ptr<Shader> shader, float initialDistance = 0.0f, int repeats = 3);
        ~Landscape();

        bool detectCollision(const ColSphereBody& target) const;
        float getHeightY(const ColSphereBody& target) const;

        void setSpeedZ(float speed);
        void incrementSpeedZ(float increment);
        float getSpeedZ();

  protected:
        virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
        bool loadTexture(std::string name, GLuint &texName);

        void initBuffers();

        float width;
        float length;
        float distance;
        float rise_;

        std::shared_ptr<Shader> shader_;

        std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
        // normal array.
        std::vector< glm::vec3 > normalArray_;
        // texture coord array
        std::vector< glm::vec2 > texCoordArray_;

        std::vector<MyVertex> combinedArray_;


        // GLuints
        GLuint texName_, VBO_, VAO_, normalMap_;

        bool texLoaded_;
        bool normalsLoaded_;

        int repeats_;
        float speed_ = 0.0f;
};

