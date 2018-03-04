//
// Created by javan on 3/3/2018.
//

#ifndef DEMOOBJ_MYMESH_H
#define DEMOOBJ_MYMESH_H


#include <vector>
#include "../common/myGLM.h"

class MyMesh {

public:
    GLuint vbo_vertices, vbo_normals, ibo_elements;
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLushort> elements;
    glm::mat4 object2world;

    MyMesh();

    ~MyMesh();


    void upload();

    void draw(GLint attribute_v_coord, GLint attribute_v_normal, GLint uniform_m,
              GLint uniform_m_3x3_inv_transp, glm::mat4 *mvpMat);

    void draw_bbox(GLuint attribute_v_coord);

};


#endif //DEMOOBJ_MYMESH_H
