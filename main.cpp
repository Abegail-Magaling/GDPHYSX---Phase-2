#include <iostream>
#include <string>
#include <chrono>
#include <limits>
#include <vector>
#include <iomanip>
#include <cmath>
#include "GameObject.h"

#include "P6/PhysicsWorld.h"
#include "P6/RenderParticle.h"
#include "P6/ParticleContact.h"
/*#include "P6/AnchoredSpring.h" */ 
#include "Camera/OrthoCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "RenderLine.h"
#include "Randomization/RandomGen.h"

#include "P6/Links/Rod.h"
#include "P6/bungee/bungee.h"
#include "P6/Chain/Chain.h"


using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

enum class CameraMode {
    Orthographic,
    Perspective
};

int main(void)
{
    float cableLength;
    float particleGap;
    float particleRadius;
    float gravityStrength;
    
    float xForce;
    float yForce;
    float zForce;
    std::cout << "Cable Length: ";
    std::cin >> cableLength;
    std::cout << "Particle Gap: ";
    std::cin >> particleGap;
    std::cout << "Particle Radius: ";
    std::cin >> particleRadius;
    std::cout << "Gravity Strength: ";
    std::cin >> gravityStrength;
    std::cout << "Apply Force: " << std::endl;
    std::cout << "x: ";
    std::cin >> xForce;
    std::cout << "y: ";
    std::cin >> yForce;
    std::cout << "z: ";
    std::cin >> zForce;

    GLFWwindow* window;
    float window_width = 800;
    float window_height = 800;

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(window_width, window_height, "Vincent Ralph N. Chang || Abegail Laureen ", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    //OrthoCamera
    auto ortho_camera = new OrthoCamera();
    ortho_camera->setCameraPosition(glm::vec3(0.0f, 0.0f, 400.0f));

    //PerspectiveCamera
    auto pers_camera = new PerspectiveCamera();
    pers_camera->setCameraPosition(glm::vec3(0, 0.f, 800.f));

    //Initiliaze PhysicsWorld
    auto pWorld = physics::PhysicsWorld(MyVector(0, gravityStrength, 0));

    //gravity
    

    //sphere
    auto sphere = GameObject("3D/sphere.obj", "Shaders/sample.vert", "Shaders/sample.frag");

    glViewport(0, 0, 800, 800);

    //Initialize RenderParticles
    std::list<RenderParticle*> RenderParticles;

    //Spawning Variables
    float fThreshHold = 0.2f;
    float fTicks = 0.0f;
    
    //Default CameraMode
    CameraMode currentCameraMode = CameraMode::Orthographic;

    //Matrices
    glm::mat4 identity_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.f);
    glm::mat4 view_matrix = glm::mat4(1.0f);

    // Pause/play flag
    bool paused = false;
    bool pressed = false;

    //Instantiating PhysicParticle
    physics::PhysicsParticle p3 = physics::PhysicsParticle();
    p3.Position = physics::MyVector(0, 100, 0);
    p3.mass = 50;
    p3.radius = particleRadius;
    pWorld.AddParticle(&p3);

    physics::PhysicsParticle p2 = physics::PhysicsParticle();
    p2.Position = physics::MyVector(p3.Position.x - particleGap, 100, 0);
    p2.mass = 50;
    p2.radius = particleRadius;
    pWorld.AddParticle(&p2);

    physics::PhysicsParticle p1 = physics::PhysicsParticle();
    p1.Position = physics::MyVector(p2.Position.x - particleGap, 100, 0);
    p1.mass = 50;
    p1.radius = particleRadius;
    pWorld.AddParticle(&p1);

    physics::PhysicsParticle p4 = physics::PhysicsParticle();
    p4.Position = physics::MyVector(p3.Position.x + particleGap, 100, 0);
    p4.mass = 50;
    p4.radius = particleRadius;
    pWorld.AddParticle(&p4);

    physics::PhysicsParticle p5 = physics::PhysicsParticle();
    p5.Position = physics::MyVector(p4.Position.x + particleGap, 100, 0);
    p5.mass = 50;
    p5.radius = particleRadius;
    pWorld.AddParticle(&p5);

    physics::MyVector springPosChain3 = physics::MyVector(0, 150, 0);
    physics::Chain chainSpring3 = Chain(springPosChain3, 0, cableLength);
    pWorld.forceRegistry.Add(&p3, &chainSpring3);

    physics::MyVector springPosChain2 = physics::MyVector(springPosChain3.x - particleGap, 150, 0);
    physics::Chain chainSpring2 = Chain(springPosChain2, 0, cableLength);
    pWorld.forceRegistry.Add(&p2, &chainSpring2);

    physics::MyVector springPosChain1 = physics::MyVector(springPosChain2.x - particleGap, 150, 0);
    physics::Chain chainSpring1 = Chain(springPosChain1, 0, cableLength);
    pWorld.forceRegistry.Add(&p1, &chainSpring1);

    physics::MyVector springPosChain4 = physics::MyVector(springPosChain3.x + particleGap, 150, 0);
    physics::Chain chainSpring4 = Chain(springPosChain4, 0, cableLength);
    pWorld.forceRegistry.Add(&p4, &chainSpring4);

    physics::MyVector springPosChain5 = physics::MyVector(springPosChain4.x + particleGap, 150, 0);
    physics::Chain chainSpring5 = Chain(springPosChain5, 0, cableLength);
    pWorld.forceRegistry.Add(&p5, &chainSpring5);


    RenderParticle rp1 = RenderParticle(&p1, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p1.radius);
    RenderParticles.push_back(&rp1);

    RenderParticle rp2 = RenderParticle(&p2, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p2.radius);
    RenderParticles.push_back(&rp2);

    RenderParticle rp3 = RenderParticle(&p3, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p3.radius);
    RenderParticles.push_back(&rp3);

    RenderParticle rp4 = RenderParticle(&p4, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p4.radius);
    RenderParticles.push_back(&rp4);

    RenderParticle rp5 = RenderParticle(&p5, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p5.radius);
    RenderParticles.push_back(&rp5);
    
    //Renderlines
    RenderLine ChainLine1 = RenderLine(springPosChain1, p1.Position, glm::vec4(1, 1, 1, 1));
    RenderLine ChainLine2 = RenderLine(springPosChain2, p2.Position, glm::vec4(1, 1, 1, 1));
    RenderLine ChainLine3 = RenderLine(springPosChain3, p3.Position, glm::vec4(1, 1, 1, 1));
    RenderLine ChainLine4 = RenderLine(springPosChain4, p4.Position, glm::vec4(1, 1, 1, 1));
    RenderLine ChainLine5 = RenderLine(springPosChain5, p5.Position, glm::vec4(1, 1, 1, 1));

    while (!glfwWindowShouldClose(window))
    {
        glClear(0x00004000);

        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;

        curr_ns += dur;


        if (curr_ns >= timestep) {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            curr_ns -= curr_ns;

            //Key inputs
            if (glfwGetKey(window, GLFW_KEY_1))
            {
                std::cout << "Switching to Orthographic Camera" << std::endl;
                currentCameraMode = CameraMode::Orthographic;
            }
            if (glfwGetKey(window, GLFW_KEY_2))
            {
                std::cout << "Switching to Perspective Camera" << std::endl;
                currentCameraMode = CameraMode::Perspective;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !pressed)
            {
                p1.AddForce(physics::MyVector(xForce, yForce, zForce));
                pressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            {
                pressed = false;
            }

            // Update cameras based on mode
            if (currentCameraMode == CameraMode::Orthographic) {
                projection_matrix = ortho_camera->getViewProjection();
                ortho_camera->Update(window, (float)ms.count() / 1000);
                view_matrix = ortho_camera->GetViewMatrix();
            }
            else if (currentCameraMode == CameraMode::Perspective) {
                projection_matrix = pers_camera->getViewProjection();
                pers_camera->Update(window, (float)ms.count() / 1000);
                view_matrix = pers_camera->GetViewMatrix();
            }

            if (!paused) {
                pWorld.Update((float)ms.count() / 1000);
            }
        }

        //Drawing Objects
        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin(); i != RenderParticles.end(); i++) {
            (*i)->Draw(identity_matrix, projection_matrix, view_matrix);
        }

        ChainLine1.Update(springPosChain1, p1.Position, projection_matrix, view_matrix);
        ChainLine1.Draw();

        ChainLine2.Update(springPosChain2, p2.Position, projection_matrix, view_matrix);
        ChainLine2.Draw();

        ChainLine3.Update(springPosChain3, p3.Position, projection_matrix, view_matrix);
        ChainLine3.Draw();

        ChainLine4.Update(springPosChain4, p4.Position, projection_matrix, view_matrix);
        ChainLine4.Draw();

        ChainLine5.Update(springPosChain5, p5.Position, projection_matrix, view_matrix);
        ChainLine5.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}