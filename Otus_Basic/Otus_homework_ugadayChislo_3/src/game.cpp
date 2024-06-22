#include <iostream>
#include <cstring>
#include <typeinfo>
#include "game.h"
#include "quess_number.h"
#include "high_score.h"

void game_loop(int current_value, int target, int &attempt)
{

    do
    {
        std::cin >> current_value;

        if (current_value < target)
        {
            std::cout << "Greater " << current_value << std::endl;
            attempt++;
        }
        else if (current_value > target)
        {
            std::cout << "Less " << current_value << std::endl;
            attempt++;
        }
        else
        {
            std::cout << "Win!" << std::endl;
            break;
        }

    } while (true);
}
void setup(int &target, int max_value)
{
    target = ZagadayChislo(max_value);
}

int run_game_processing(int argc, char **argv)
{
    // int result;

    person Player;
    int max_value = 100;
    if (argc > 1 && !std::strcmp(argv[1], "-max") && (argv[2]) && std::atoi(argv[2]) > 0)
        max_value = atoi(argv[2]);
    else if (argc > 1 && !std::strcmp(argv[1], "-table"))
    {
        ReadFile();
        return 0;
    }
    else if (argc > 1 && !std::strcmp(argv[1], "-level") && (argv[2]) && atoi(argv[2]) > 0)
        switch (atoi(argv[2]))
        {
        case 1:
            max_value = 10;
            break;
        case 2:
            max_value = 50;
            break;
        case 3:
            max_value = 100;
            break;
        default:
            break;
        }
    else
        max_value = 100;
    Player.attempt = 1;

    int target;
    int current_value = 0;
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::cin >> Player.user_name;

    setup(target, max_value);

    std::cout << target << std::endl; // лень
    std::cout << Player.user_name << " enter your guess:" << std::endl;

    game_loop(current_value, target, Player.attempt);
    CreateandWriteinFile(Player);
    ReadFile();

    return 1;
}