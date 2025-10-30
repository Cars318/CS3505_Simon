#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @brief The GameState enum provides different game states:
 * Initial: The start of the game, before play has begun
 * Computer: The computer's automated actions, disables player action
 * Player: The player's actions
 */
enum GameState {
    Initial = 1,
    Computer = 2,
    Player = 3,
};

#endif // GAMESTATE_H
