

#include <GL/glew.h>

#include "scene.hpp"
#include "../../lib/opengl/glutils.hpp"

#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include "../interface/myWidgetGL.hpp"

#include <cmath>


#include <string>
#include <sstream>
#include "../../lib/mesh/mesh_io.hpp"

int init=0;
int k;

using namespace cpe;


static cpe::mesh build_ground(float const L,float const h)
{
    mesh m;
    m.add_vertex(vec3(-L, h,-L));
    m.add_vertex(vec3(-L, h, L));
    m.add_vertex(vec3( L, h, L));
    m.add_vertex(vec3( L, h,-L));

    m.add_triangle_index({0,2,1});
    m.add_triangle_index({0,3,2});

    m.fill_color(vec3(0.8,0.9,0.8));

    return m;
}


static cpe::mesh_skinned build_cylinder(float const h, float const r, int const Nl, int const Nc)
{
    mesh_skinned m;
    int count = 0;

    vertex_weight_parameter tab_poids;
    for (int i=0; i<Nl; i++ )
    {
        for (int j =0; j < Nc; j++)
        {
            count +=1;
            m.add_vertex(vec3(r*cos(2*j*M_PI/Nc),r*sin(2*j*M_PI/Nc) ,h*((float)i/(Nl-1))));

            tab_poids[0].joint_id = 0;
            tab_poids[0].weight = 1-float(i)/(Nl-1);
            tab_poids[1].joint_id = 1;
            tab_poids[1].weight = float(i)/(Nl-1);

            m.add_vertex_weight(tab_poids);
        }
    }
    for (int i=0; i<Nl-1; i++ )
    {
        for (int j =0; j < Nc; j++)
        {
            m.add_triangle_index({j + i*Nc, (j+1)%Nc + i*Nc, j + (i+1)*Nc});
            m.add_triangle_index({(j+1)%Nc + i*Nc,(j+1)%Nc + (i+1)*Nc, j + (i+1)*Nc});
        }
    }

    m.fill_color(vec3(0.9,0.1,0.1));

    return m;
}


void scene::load_scene()
{


    //*****************************************//
    // Preload default structure               //
    //*****************************************//
    texture_default = load_texture_file("data/white.jpg");
    shader_mesh     = read_shader("shaders/shader_mesh.vert",
                                  "shaders/shader_mesh.frag");           PRINT_OPENGL_ERROR();
    shader_skeleton = read_shader("shaders/shader_skeleton.vert",
                                  "shaders/shader_skeleton.frag");       PRINT_OPENGL_ERROR();


    //*****************************************//
    // Build ground
    //*****************************************//
    mesh_ground = build_ground(100.0f , -25.0f);
    mesh_ground.fill_empty_field_by_default();
    mesh_ground_opengl.fill_vbo(mesh_ground);


    float h = 100.0;
    float r = 20.0;
    int Nl = 10;
    int Nc = 16;
    mesh_cylinder = build_cylinder(h, r, Nl, Nc);
    mesh_cylinder.fill_empty_field_by_default();
    mesh_cylinder_opengl.fill_vbo(mesh_cylinder);

    sk_cylinder_parent_id.push_back(-1);
    sk_cylinder_parent_id.push_back(0);
    sk_cylinder_parent_id.push_back(1);


    quaternion q = quaternion(0.0,0.0,0.0,1.0);

    skeleton_joint j0 = skeleton_joint(vec3(0,0,0),q);
    skeleton_joint j1 = skeleton_joint(vec3(0,0,h/2),q);
    skeleton_joint j2 = skeleton_joint(vec3(0,0,h/2),q);




    sk_cylinder_bind_pose.push_back(j0);
    sk_cylinder_bind_pose.push_back(j1);
    sk_cylinder_bind_pose.push_back(j2);

    build_animation_skeleton(vec3(0.0,1.0,0.0), M_PI/2, 4);

}


void scene::build_animation_skeleton(vec3 axis, float angle_final, int nb_it)
{
    sk_cylinder_animation.push_back(sk_cylinder_bind_pose);

    skeleton_joint j0 = sk_cylinder_bind_pose[0];
    skeleton_joint j1 = sk_cylinder_bind_pose[1];
    skeleton_joint j2 = sk_cylinder_bind_pose[2];
    cpe::skeleton_geometry sk_cylinder;

    for(int i=1;i<nb_it;i++)
    {

        quaternion q; q.set_axis_angle(axis,i*angle_final/(nb_it-1));
        //j1 = skeleton_joint(vec3(0,0,h/2),q);
        j1.orientation = q;
        sk_cylinder.push_back(j0);
        sk_cylinder.push_back(j1);
        sk_cylinder.push_back(j2);
        sk_cylinder_animation.push_back(sk_cylinder);
        sk_cylinder.clear();
    }


}


void scene::draw_scene()
{

    setup_shader_skeleton(shader_skeleton);

    if (init==0)
    {
        tps.start();
        k = 0;
        init++;
    }


    if (tps.elapsed() >= 1000)
    {
        k++;
        if( k== 4)
            k = 0;
        tps.restart();
    }



    skeleton_geometry const sk_cylinder_global = local_to_global(sk_cylinder_animation[k], sk_cylinder_parent_id);
    std::vector<vec3> const sk_cylinder_bones = extract_bones(sk_cylinder_global,sk_cylinder_parent_id);
    draw_skeleton(sk_cylinder_bones);
    //Here we can draw skeletons as 3D segments

    setup_shader_mesh(shader_mesh);

    mesh_ground_opengl.draw();

    //mesh_cylinder_opengl.draw();

    skeleton_geometry const sk_cylinder_inverse_bind_pose =
    inversed(sk_cylinder_bind_pose);
    skeleton_geometry const sk_cylinder_binded =
    multiply(sk_cylinder_global,sk_cylinder_inverse_bind_pose);
    mesh_cylinder.apply_skinning(sk_cylinder_binded);
    mesh_cylinder.fill_normal();
    mesh_cylinder_opengl.update_vbo_vertex(mesh_cylinder);
    mesh_cylinder_opengl.update_vbo_normal(mesh_cylinder);
    mesh_cylinder_opengl.draw();



}


void scene::setup_shader_mesh(GLuint const shader_id)
{
    //Setup uniform parameters
    glUseProgram(shader_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();

    //load white texture
    glBindTexture(GL_TEXTURE_2D,texture_default);                                                      PRINT_OPENGL_ERROR();
    glLineWidth(1.0f);                                                                                 PRINT_OPENGL_ERROR();

}

void scene::setup_shader_skeleton(GLuint const shader_id)
{
    //Setup uniform parameters
    glUseProgram(shader_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniform3f(get_uni_loc(shader_id,"color") , 0.0f,0.0f,0.0f);                                      PRINT_OPENGL_ERROR();

    //size of the lines
    glLineWidth(3.0f);                                                                                 PRINT_OPENGL_ERROR();
}

void scene::draw_skeleton(std::vector<vec3> const& positions) const
{
    // Create temporary a VBO to store data
    GLuint vbo_skeleton=0;
    glGenBuffers(1,&vbo_skeleton);                                                                     PRINT_OPENGL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER,vbo_skeleton);                                                        PRINT_OPENGL_ERROR();

    // Update data on the GPU
    glBufferData(GL_ARRAY_BUFFER , sizeof(vec3)*positions.size() , &positions[0] , GL_STATIC_DRAW);    PRINT_OPENGL_ERROR();

    // Draw data
    glEnableClientState(GL_VERTEX_ARRAY);                                                              PRINT_OPENGL_ERROR();
    glVertexPointer(3, GL_FLOAT, 0, 0);                                                                PRINT_OPENGL_ERROR();
    glDrawArrays(GL_LINES,0,positions.size());                                                         PRINT_OPENGL_ERROR();

    // Delete temporary VBO
    glDeleteBuffers(1,&vbo_skeleton);                                                                  PRINT_OPENGL_ERROR();
}

scene::scene()
    :shader_mesh(0)
{}


GLuint scene::load_texture_file(std::string const& filename)
{
    return pwidget->load_texture_file(filename);
}

void scene::set_widget(myWidgetGL* widget_param)
{
    pwidget=widget_param;
}


