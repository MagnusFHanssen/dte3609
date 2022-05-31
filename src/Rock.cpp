#include "../include/Rock.hpp"
#include <iostream>


#include "../include/stb_image.h"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

Rock::Rock(std::shared_ptr<Shader> shader, std::shared_ptr<Landscape> ls, std::shared_ptr<Model> model):
    shader_{shader}, ls_{ls}, model_{model}
{
    gravity = {0.0f, -9.81f, 0.0f};
    attached = false;
}

Rock::~Rock(){}

void Rock::privateInit(){

}


