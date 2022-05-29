#include "../include/Text.hpp"

Text::Text(std::string string, glm::vec3 pos, void* font, int type, glm::vec3 color):
    pos_{pos}, font_{font}, string_{string}, type_{type}, color_{color}{}

// Stroke Fonts
//GLUT_STROKE_ROMAN
//GLUT_STROKE_MONO_ROMAN
void Text::strokeCharacter(){
    glTranslatef(pos_.x, pos_.y, pos_.z);
    glLineWidth(10.0f);

    for (char& c: string_){
        glutStrokeCharacter(font_, c);
    }

    glLineWidth(1.0f);
}

// Bitmap Fonts
//GLUT_BITMAP_8_BY_13
//GLUT_BITMAP_9_BY_15
//GLUT_BITMAP_TIMES_ROMAN_10
//GLUT_BITMAP_TIMES_ROMAN_24
//GLUT_BITMAP_HELVETICA_10
//GLUT_BITMAP_HELVETICA_12
//GLUT_BITMAP_HELVETICA_18
void Text::bitmapCharacter(){
    glRasterPos3f(pos_.x, pos_.y, pos_.z);

    for(char& c: string_){
        glutBitmapCharacter(font_, c);
    }
}

void Text::privateInit(){}

void Text::privateUpdate(){}

void Text::privateRender(){
    glColor3f(color_.r, color_.g, color_.b);

    glPushMatrix();{
        glScalef(1.0f/100.0f, 1.0f/100.0f, 1.0f);
    }
    switch (type_) {
    case BITMAP_CHAR:
        bitmapCharacter();
        break;
    case STROKE_CHAR:
        strokeCharacter();
        break;
    }
    glPopMatrix();
}

void Text::setString(std::string string){
    string_ = string;
}


