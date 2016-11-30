// Copyright (c) <2016>, <Nanyang Technological University> All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "robot.h"

Robot::Robot()
{
    vertex_init = new g2o::VertexSE3();

    vertex_init->setId(ID);

    vertex_init->setEstimate(Eigen::Isometry3d::Identity());

    poses_number = 0;
}


g2o::VertexSE3* Robot::new_vertex(unsigned char type)
{
    if(FLAG_STATIC)
        return last_vertex(type);
    else
    {
        poses_number++;

        g2o::VertexSE3* vertex = new g2o::VertexSE3();

        vertex->setId(ID + poses_number*10);

        vertex->setEstimate(last_vertex(type)->estimate());

        vertices[type].push_back(vertex);

        vertex_number[type]++;

        return vertex;
    }
}

g2o::VertexSE3* Robot::last_vertex(unsigned char type)
{
    vertex_number.insert({type,0});

    if (vertex_number[type] == 0)
        vertices[type].push_back(vertex_init);

    return vertices[type].back();
}