//
// Created by SJHCN on 2022/7/15.
//

#include "look_at.h"
#include "../glm_util.h"

void LookAt::draw() {

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0F, 0.1F, 0.0F));



}
