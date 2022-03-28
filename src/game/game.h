#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "engine/audio/audio_manager.h"
#include "engine/shader/shader.h"
#include "engine/texture_library.h"
#include "entities/bullet.h"
#include "entities/enemy_entity.h"
#include "entities/player_entity.h"
#include "object/collider.h"
#include "object/colliders/circle_collider.h"
#include "object/colliders/ray_collider.h"
#include "object/effect_object.h"
#include "object/follower_object.h"
#include "object/game_object.h"
#include "object/followers/shield.h"
#include "entities/collectibles/addshield.h"
#include "entities/enemies/buoy.h"


namespace game
{

  // A class for holding the main game objects
  class Game
  {

  public:
    // Constructor and destructor
    Game(void);
    ~Game();

    // Call Init() before calling any other method
    // Initialize graphics libraries and main window
    void Init(void);

    // Set up the game (scene, game objects, etc.)
    void Setup(void);

    // Run the game (keep the game active)
    void MainLoop(void);

    inline audio_manager::AudioManager *GetAudioManager(void) { return am_; }
    void PlaySoundOfIndex(int index);

    void SpawnEnemies(int amount);
    void SpawnCollectibles(int amount);
    void AddEnemy(const glm::vec3 &position, GLuint texture, GLint num_elements, EffectObject *effect, float seeRadius, float speed);

        private :
        // Main window: pointer to the GLFW window structure
        GLFWwindow *window_;

    // Shader for rendering the scene
    Shader shader_;

    Shader grey_shader_;

    // Size of geometry to be rendered
    int size_;

    float camera_zoom_;

    audio_manager::AudioManager *am_;
    engine::TextureLibrary tex_library_;

    // List of game objects
    std::vector<GameObject *> game_objects_;
    std::vector<Entity *> collidables_;
    std::vector<EnemyEntity *> enemies_;

    PlayerEntity* player_;

    // Callback for when the window is resized
    static void ResizeCallback(GLFWwindow *window, int width, int height);

    // Create a square for drawing textures
    int CreateSprite(void);

    // Handle user input
    void Controls(void);

    // Update the game based on user input and simulation
    void Update(double delta_time);

    void Draw();

    void UpdateGameObjects(double delta_time);

    void CheckEnemies();

    void CheckCollisions();

    bool GetCursorPos(glm::vec2* vec);

    bool CheckForDeletion(std::vector<GameObject *> layer, int position);
    void DeleteGameObject(std::vector<GameObject *> layer, int position);

  }; // class Game

} // namespace game

#endif // GAME_H_
