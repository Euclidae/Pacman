#include "ghost.hpp"
#include "globals.hpp"

// Create a single global random number generator to avoid reseeding problems
static std::mt19937 global_generator(static_cast<unsigned int>(std::time(nullptr)));

int random_between(int x, int y) {
    // Handle invalid ranges
    if (y < x) {
        std::swap(x, y);
    }

    // If x and y are the same or 1 apart, just return x
    if (y - x <= 1) {
        return x;
    }

    // For normal cases with range > 1
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(global_generator);
}

Ghost::Ghost(std::string image, SDL_Renderer* renderer, mat::vector2f pos, mat::vector2f move_speed, Direction def, std::string n) : sprite(image), position(pos), move_speed(move_speed) {
    frames = Animation(sprite, renderer, mat::vector2f{CELL_SIZE, 31}, position);
    destination = {position.x, position.y, (float)SCREEN_WIDTH/COLUMNS - 2, (float)SCREEN_HEIGHT/ROWS - 2};
    direction = def;
    name = n;
    vessel = destination; // Initialize vessel to avoid undefined behavior

    // Initialize with a valid direction
    possible_directions.push_back(def);
}

void Ghost::draw(float time) {
    frames.change_sprite(direction);
    frames.animate(time);
    frames.draw_entity(destination);
}

void Ghost::change_mode() {
    // Implementation for mode changes
}

void Ghost::detect_collision(Pacman& pacman) {
    // Pacman collision detection
}

bool Ghost::detect_collision(Map& map, SDL_FRect& spider) {
    for(auto& content: map.getMap()) {
        if(spider.x < content.x + content.w && spider.x + spider.w > content.x &&
           spider.y < content.y + content.h && spider.y + spider.h > content.y) {
            return true;
        }
    }
    return false;
}

void Ghost::flee(bool flee) {
    // Implementation for flee behavior
}

void Ghost::change_direction(Map& map) {
    // Debug output
    for(auto i: possible_directions) {
        if (i == UP) {
            std::cout << name << " P.UP\n";
        } else if (i == DOWN) {
            std::cout << name << " P.DOWN\n";
        } else if (i == LEFT) {
            std::cout << name << " P.LEFT\n";
        } else if (i == RIGHT) {
            std::cout << name << " P.RIGHT\n";
        }
    }

    // Ensure we always have at least one direction
    if(possible_directions.empty()) {
        std::cout << name << " has empty possible_directions vector!\n";

        // As a fallback, try all directions and pick one that doesn't cause collision
        SDL_FRect test_vessel = destination;
        Direction fallback_directions[] = {UP, DOWN, LEFT, RIGHT};

        for (auto dir : fallback_directions) {
            test_vessel = destination; // Reset

            // Test each direction with a small movement
            float test_dist = 2.0f; // Small test distance
            if (dir == UP) test_vessel.y -= test_dist;
            else if (dir == DOWN) test_vessel.y += test_dist;
            else if (dir == LEFT) test_vessel.x -= test_dist;
            else if (dir == RIGHT) test_vessel.x += test_dist;

            if (!detect_collision(map, test_vessel)) {
                possible_directions.push_back(dir);
                std::cout << name << " added fallback direction: " << dir << std::endl;
            }
        }

        // If still empty (ghost is trapped), default to current direction
        if (possible_directions.empty()) {
            std::cout << name << " is trapped! Using current direction as fallback\n";
            possible_directions.push_back(direction);
        }
    }

    // Choose a random valid direction
    int index = possible_directions.size() == 1 ? 0 : random_between(0, possible_directions.size() - 1);
    direction = possible_directions[index];
    std::cout << name << " chose direction: " << direction << std::endl;

    // Clear possible directions for next update
    possible_directions.clear();
}

// Recommended changes to fix ghost movement issues

void Ghost::update(float delta_time, Map& map) {
    // Debug movement speed
    std::cout << name << " Move vector x: " << move_speed.x << std::endl;
    std::cout << name << " Move vector y: " << move_speed.y << std::endl;

    SDL_FRect spider = destination;
    float x_move_speed = (move_speed.x * delta_time);
    float y_move_speed = (move_speed.y * delta_time);

    // Apply movement based on current direction
    switch(direction) {
        case UP:
            std::cout << name << " goes up" << std::endl;
            spider.y -= y_move_speed;
            break;
        case DOWN:
            std::cout << name << " goes down" << std::endl;
            spider.y += y_move_speed;
            break;
        case LEFT:
            std::cout << name << " goes left" << std::endl;
            spider.x -= x_move_speed;
            break;
        case RIGHT:
            std::cout << name << " goes right" << std::endl;
            spider.x += x_move_speed;
            break;
    }

    // Check if we're at a junction (allow a small error margin for alignment)
    bool at_junction = false;
    const float GRID_ALIGN_THRESHOLD = 2.0f;  // Pixels of error margin

    // Check if we're aligned to the grid (proper junction detection)
    bool aligned_to_grid = false;
    float grid_x = std::round(destination.x / CELL_SIZE) * CELL_SIZE;
    float grid_y = std::round(destination.y / CELL_SIZE) * CELL_SIZE;

    if (std::abs(destination.x - grid_x) < GRID_ALIGN_THRESHOLD &&
        std::abs(destination.y - grid_y) < GRID_ALIGN_THRESHOLD) {
        aligned_to_grid = true;

        // Get possible directions at this location
        get_possible_directions(map, destination, delta_time);

        // If we have more than one option (excluding going backwards), we're at a junction
        if (possible_directions.size() >= 2) {
            at_junction = true;
        }
    }

    // Handle collision with the map
    if(detect_collision(map, spider)) {
        spider = destination; // Reset to original position

        // Get new possible directions and change
        get_possible_directions(map, spider, delta_time);
        change_direction(map);

        // Apply the new direction
        switch(direction) {
            case UP:
                spider.y -= y_move_speed;
                break;
            case DOWN:
                spider.y += y_move_speed;
                break;
            case LEFT:
                spider.x -= x_move_speed;
                break;
            case RIGHT:
                spider.x += x_move_speed;
                break;
        }

        // If we still have a collision, don't move this frame
        if(detect_collision(map, spider)) {
            spider = destination;
        }
    } else {
        // If we're at a junction, consider changing direction
        if (at_junction) {
            // Consistent junction handling for all ghosts
            // Blue and orange ghosts have increased probability to take turns
            int change_probability = 60; // Default 30% chance to turn at junction

            // For blue and orange, increase turning probability when headed in their default directions
            if ((name == "blue" && direction == RIGHT) ||
                (name == "orange" && direction == LEFT)) {
                change_probability = 60; // 60% chance to change at junction
            }

            // Check if we should change direction
            if (random_between(0, 99) < change_probability) {
                change_direction(map);

                // Recalculate next position with new direction
                spider = destination;
                switch(direction) {
                    case UP:
                        spider.y -= y_move_speed;
                        break;
                    case DOWN:
                        spider.y += y_move_speed;
                        break;
                    case LEFT:
                        spider.x -= x_move_speed;
                        break;
                    case RIGHT:
                        spider.x += x_move_speed;
                        break;
                }
            }
        }
    }

    // Handle screen wrapping correctly
    if(spider.x > SCREEN_WIDTH) {
        spider.x = 0 - spider.w;
    }
    if(spider.x + spider.w < 0) {
        spider.x = SCREEN_WIDTH;
    }
    if(spider.y > SCREEN_HEIGHT) {
        spider.y = 0 - spider.h;
    }
    if(spider.y + spider.h < 0) {
        spider.y = SCREEN_HEIGHT;
    }

    // Update ghost position
    destination = spider;
}

void Ghost::get_possible_directions(Map& map, SDL_FRect& spider, float delta_time) {
    // Use a fixed test distance rather than delta-time based for consistency
    const float TEST_DISTANCE = 2.0f;

    // Clear previous possible directions
    possible_directions.clear();

    Direction opposite;
    Direction compass[] = {UP, DOWN, LEFT, RIGHT};

    // Determine opposite direction to avoid backtracking
    switch(direction) {
        case UP:
            opposite = DOWN;
            break;
        case DOWN:
            opposite = UP;
            break;
        case LEFT:
            opposite = RIGHT;
            break;
        case RIGHT:
            opposite = LEFT;
            break;
    }

    // Test each direction
    for(int i = 0; i < 4; ++i) {
        Direction dir = compass[i];
        if(dir == opposite) continue; // Skip opposite direction

        vessel = spider; // Reset test vessel to current position

        switch(dir) {
            case RIGHT:
                vessel.x += TEST_DISTANCE;
                if(!detect_collision(map, vessel)) {
                    possible_directions.push_back(dir);
                    std::cout << name << " possible right\n";
                }
                break;
            case LEFT:
                vessel.x -= TEST_DISTANCE;
                if(!detect_collision(map, vessel)) {
                    possible_directions.push_back(dir);
                    std::cout << name << " possible left\n";
                }
                break;
            case UP:
                vessel.y -= TEST_DISTANCE;
                if(!detect_collision(map, vessel)) {
                    possible_directions.push_back(dir);
                    std::cout << name << " possible up\n";
                }
                break;
            case DOWN:
                vessel.y += TEST_DISTANCE;
                if(!detect_collision(map, vessel)) {
                    possible_directions.push_back(dir);
                    std::cout << name << " possible down\n";
                }
                break;
        }
    }

    // If no valid directions and ghost is trapped:
    // 1. Try the opposite direction as a last resort
    // 2. But only after confirming it won't cause collision
    if(possible_directions.empty()) {
        vessel = spider;
        switch(opposite) {
            case RIGHT:
                vessel.x += TEST_DISTANCE;
                break;
            case LEFT:
                vessel.x -= TEST_DISTANCE;
                break;
            case UP:
                vessel.y -= TEST_DISTANCE;
                break;
            case DOWN:
                vessel.y += TEST_DISTANCE;
                break;
        }

        if(!detect_collision(map, vessel)) {
            possible_directions.push_back(opposite);
            std::cout << name << " forced to use opposite direction: " << opposite << std::endl;
        } else {
            // Ghost is completely trapped - maintain current direction and hope map design prevents this
            possible_directions.push_back(direction);
            std::cout << name << " is completely trapped! Maintaining current direction\n";
        }
    }
}
