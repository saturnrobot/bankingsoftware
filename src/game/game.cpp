#include <SOIL/SOIL.h>
#include <cstddef>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../bin/path_config.h"

#include "entities/entity.h"
#include "game.h"
#include "object/game_object.h"

namespace game
{

    // Some configuration constants
    // They are written here as global variables, but ideally they should be loaded from a configuration file

    // Globals that define the OpenGL window and viewport
    const char *window_title_g = "Assignment 4";
    const unsigned int window_width_g = 800;
    const unsigned int window_height_g = 600;
    const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);

    // Directory with game resources such as textures
    const std::string resources_directory_g = RESOURCES_DIRECTORY;

    Game::Game(void)
    {
        // Don't do work in the constructor, leave it for the Init() function
    }

    void Game::Init(void)
    {

        // Initialize the window management library (GLFW)
        if (!glfwInit())
        {
            throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
        }

        // Set window to not resizable
        // Required or else the calculation to get cursor pos to screenspace will be incorrect
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Create a window and its OpenGL context
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
        if (!window_)
        {
            glfwTerminate();
            throw(std::runtime_error(std::string("Could not create window")));
        }

        // Make the window's OpenGL context the current one
        glfwMakeContextCurrent(window_);

        // Initialize the GLEW library to access OpenGL extensions
        // Need to do it after initializing an OpenGL context
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
        }

        am_ = new audio_manager::AudioManager();
        am_->Init(NULL);
        am_->SetListenerPosition(0.0, 0.0, 0.0);

        // Set event callbacks
        glfwSetFramebufferSizeCallback(window_, ResizeCallback);

        // Set up square geometry
        size_ = CreateSprite();

        // Initialize shader
        shader_.Init((resources_directory_g + std::string("/shaders/vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/shaders/fragment_shader.glsl")).c_str());
        shader_.Enable();

        // Set up z-buffer for rendering
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Enable Alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Game::~Game()
    {
        am_->ShutDown();
        delete am_;
        game_objects_.clear();
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    void Game::Setup(void)
    {

        camera_zoom_ = 0.25f;

        tex_library_.SetAllTextures();

        std::string filename = std::string(AUDIO_DIRECTORY).append(std::string("/").append(std::string("jazz.wav")));
        am_->AddSound(filename.c_str());
        am_->SetSoundPosition(0, -10.0, 0.0, 0.0);
        am_->SetLoop(0, true);
        // am_->PlaySound(0);

        int sound_index;
        filename = std::string(AUDIO_DIRECTORY).append(std::string("/").append(std::string("you_lose.wav")));
        sound_index = am_->AddSound(filename.c_str());

        // Setup the player object (position, texture, vertex count)
        // Note that, in this specific implementation, the player object should always be the first object in the game object vector
        EffectObject *effect = new EffectObject(glm::vec3(0.0f, 0.0f, 0.0f), tex_library_.GetTexture("explosion_basic"), size_, 0.8, sound_index);
        Bullet *bullet = new Bullet(glm::vec3(0.0f, 0.0f, 0.0f), tex_library_.GetTexture("bullet"), size_, new RayCollider("bullet"), new EffectObject(*effect), 20, 0.5);
        player_ = new PlayerEntity(glm::vec3(0.0f, 0.0f, 0.0f), tex_library_.GetTexture("player"), size_, new CircleCollider("player"), effect, 0.1, 3, bullet, 0.4);
        player_->AddChild(new FollowerObject(player_->GetPosition(), tex_library_.GetTexture("chopper_blade"), size_, glm::vec3(0.0f, 0.1f, -1.0)));
        player_->AddChild(new Shield(player_->GetPosition(), tex_library_.GetTexture("player"), size_, player_, new Orbiter(player_->GetPosition(), tex_library_.GetTexture("orb"), size_, 2, 1.5, player_->GetPosition())));
        game_objects_.push_back(player_);
        collidables_.push_back(player_);

        // Setup other objects
        SpawnCollectibles(5);
        SpawnEnemies(5);

        //These things are stupid
        /*Buoy *small_guy = new Buoy(glm::vec3(1,1,0), tex_library_.GetTexture("buoy"), size_, new CircleCollider("buoy", 0.7), new EffectObject(*effect), 1);
        game_objects_.push_back(small_guy);
        collidables_.push_back(small_guy);

        Buoy *big_guy = new Buoy(glm::vec3(-2,1,0), tex_library_.GetTexture("buoy2"), size_, new CircleCollider("buoy", 0.7), new EffectObject(*effect), 3);
        game_objects_.push_back(big_guy);
        collidables_.push_back(big_guy);*/

        for (int y = -5; y < 5; ++y)
        {
            for (int x = -5; x < 5; ++x)
            {
                GameObject *background = new GameObject(glm::vec3(x, y, 0.0f), tex_library_.GetTexture("background"), size_, false);
                background->SetScale(20.0);
                game_objects_.push_back(background);
            }
        }
        // game_objects_.push_back(e);

        for (GameObject *g : game_objects_)
        {
            g->Init();
        }
    }

    void Game::PlaySoundOfIndex(int index)
    {
        am_->PlaySound(index);
    }

    void Game::SpawnEnemies(int amount)
    {
        for (int i = 0; i < amount; ++i)
        {
            int sign = 1;
            if (randf() > 0.5)
            {
                sign *= -1;
            }
            float x = sign * randf(2, 7);
            if (randf() > 0.5)
            {
                sign *= -1;
                ;
            }
            float y = sign * randf(2, 7);
            Game::AddEnemy(glm::vec3(x, y, 0.0f), tex_library_.GetTexture("enemy_basic"), size_, new EffectObject(glm::vec3(0.0f, 0.0f, 0.0f), tex_library_.GetTexture("explosion_basic"), size_, 0.8, 1), 3, 10);
        }
    }

    void Game::SpawnCollectibles(int amount)
    {
        for (int i = 0; i < amount; ++i)
        {
            int sign = 1;
            if (randf() > 0.5)
            {
                sign *= -1;
            }
            float x = sign * randf(2, 7);
            if (randf() > 0.5)
            {
                sign *= -1;
                ;
            }
            float y = sign * randf(2, 7);

            if (randf() > 0.5)
            {
                AddShield *c = new AddShield(glm::vec3(x, y, 0.0f), tex_library_.GetTexture("shield_c"), size_, new CircleCollider("collectible"), new EffectObject(glm::vec3(0.0f, 0.0f, 0.0f), tex_library_.GetTexture("explosion_basic"), size_, 0.8, 1));
                game_objects_.push_back(c);
                collidables_.push_back(c);
            }
            else
            {
                AddShield *c = new AddShield(glm::vec3(x, y, 0.0f), tex_library_.GetTexture("shield_c"), size_, new CircleCollider("collectible"), new EffectObject(glm::vec3(0.0f, 0.0f, 0.0f), tex_library_.GetTexture("explosion_basic"), size_, 0.8, 1));
                game_objects_.push_back(c);
                collidables_.push_back(c);
            }
        }
    }

    void Game::AddEnemy(const glm::vec3 &position, GLuint texture, GLint num_elements, EffectObject *effect, float seeRadius, float speed)
    {
        EnemyEntity *enemy = new EnemyEntity(position, texture, num_elements, seeRadius, new CircleCollider("enemy"), effect, speed);
        game_objects_.push_back(enemy);
        enemies_.push_back(enemy);
        collidables_.push_back(enemy);
    }

    void Game::MainLoop(void)
    {

        // Loop while the user did not close the window
        double lastTime = glfwGetTime();
        while (!glfwWindowShouldClose(window_))
        {

            // Clear background
            glClearColor(viewport_background_color_g.r, viewport_background_color_g.g, viewport_background_color_g.b, 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Set view to zoom out, centered by default at 0,0
            glm::vec3 viewPos = game_objects_[0]->GetPosition();
            viewPos = glm::vec3(viewPos.x * -1, viewPos.y * -1, viewPos.z);
            glm::mat4 view_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom_, camera_zoom_, camera_zoom_)) * glm::translate(glm::mat4(1.0f), viewPos);
            shader_.SetUniformMat4("view_matrix", view_matrix);

            // Calculate delta time
            double currentTime = glfwGetTime();
            double deltaTime = currentTime - lastTime;

            lastTime = currentTime;

            // Update the game
            Update(deltaTime);

            // Push buffer drawn in the background onto the display
            glfwSwapBuffers(window_);

            // Update other events like input handling
            glfwPollEvents();
        }
    }

    void Game::ResizeCallback(GLFWwindow *window, int width, int height)
    {

        // Set OpenGL viewport based on framebuffer width and height
        glViewport(0, 0, width, height);
    }

    // Create the geometry for a sprite (a squared composed of two triangles)
    // Return the number of array elements that form the square
    int Game::CreateSprite(void)
    {
        // The face of the square is defined by four vertices and two triangles

        // Number of attributes for vertices and faces
        // const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
        // const int face_att = 3; // Vertex indices (3)

        GLfloat vertex[] = {
            // Four vertices of a square
            // Position      Color                Texture coordinates
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // Bottom-left
        };

        // Two triangles referencing the vertices
        GLuint face[] = {
            0, 1, 2, // t1
            2, 3, 0  // t2
        };

        // OpenGL buffers
        GLuint vbo, ebo;
        // Create buffer for vertices
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

        // Create buffer for faces (index buffer)
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

        // Return number of elements in array buffer (6 in this case)
        return sizeof(face) / sizeof(GLuint);
    }

    void Game::Controls(void)
    {
        if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window_, true);
        }

        if (player_->Paused())
            return;

        // Check for player input and make changes accordingly
        if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
        {
            player_->MoveForward();
        }
        if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
        {
            player_->MoveBackward();
        }
        if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
        {
            //player_->RotateLeft();
        }
        if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
        {
            //player_->RotateRight();
        }

        if ((glfwGetKey(window_, GLFW_KEY_A) == GLFW_RELEASE) && (glfwGetKey(window_, GLFW_KEY_D) == GLFW_RELEASE) && (glfwGetKey(window_, GLFW_KEY_S) == GLFW_RELEASE) && (glfwGetKey(window_, GLFW_KEY_W) == GLFW_RELEASE))
        {
            player_->Stop();
        }
        if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            player_->Shoot(glm::vec3(player_->GetPosition().x, player_->GetPosition().y, -1.0f), player_->GetRotation());
        }
        glm::vec2 cursor_pos;
        if(GetCursorPos(&cursor_pos)) {
            player_->LookAtPoint(cursor_pos);
        }
    }

    bool Game::GetCursorPos(glm::vec2 *vec)
    {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);
        int window_width, window_height;
        glfwGetWindowSize(window_, &window_width, &window_height);
        if (x < 0 || x > window_width || y < 0 || y > window_height)
        {
            return false;
        }
        float w = window_width;
        float h = window_height;
        float aspect_ratio = w / h;
        float cursor_x_pos = ((2.0f * x - w) * aspect_ratio) / (w * camera_zoom_);
        float cursor_y_pos = (-2.0f * y + h) / (h * camera_zoom_);
        *vec = glm::vec2(cursor_x_pos + player_->GetPosition().x, cursor_y_pos + player_->GetPosition().y);
        return true;
    }

    void Game::Update(double delta_time)
    {
        // Handle user input
        Controls();
        UpdateGameObjects(delta_time);
        CheckEnemies();
        CheckCollisions();
        Draw();
    }

    void Game::UpdateGameObjects(double delta_time)
    {
        // Update and render all game objects
        for (std::vector<GameObject *>::iterator current_game_object = game_objects_.begin(); current_game_object != game_objects_.end();)
        {
            (*current_game_object)->Update(delta_time);
            if ((*current_game_object)->MarkedForDeletion() && (*current_game_object) != player_)
            {
                game_objects_.erase(current_game_object);
            }
            else
            {
                ++current_game_object;
            }
        }
    }

    void Game::CheckCollisions()
    {
        // Check for collision with other game objects
        for (std::vector<Entity *>::iterator col1 = collidables_.begin(); col1 != collidables_.end();)
        {
            for (std::vector<Entity *>::iterator col2 = col1 + 1; col2 != collidables_.end(); ++col2)
            {
                if ((*col1)->CheckCollisionEntity((*col2)) || (*col2)->CheckCollisionEntity((*col1)))
                {
                    // Play Sound
                }
            }
            if ((*col1)->MarkedForDeletion())
            {
                collidables_.erase(col1);
            }
            else
            {
                ++col1;
            }
        }

        player_->CheckBulletCollisions(player_, collidables_);
    }

    void Game::CheckEnemies()
    {
        for (EnemyEntity *enemy : enemies_)
        {
            float distance = glm::length(enemy->GetPosition() - game_objects_[0]->GetPosition());
            if (distance < enemy->GetSeeRadius() && !player_->Paused())
            {
                enemy->SetTarget(game_objects_[0]->GetPosition());
                enemy->SetChase();
            }
        }
    }

    void Game::Draw()
    {
        for (GameObject *obj : game_objects_)
            obj->Render(shader_);
    }
} // namespace game