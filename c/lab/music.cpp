#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    // Play a WAV file using a system command
    int result = system("aplay /home/chirag/Projects/college/c/lab/music.wav");

    if (result == 0) {
        std::cout << "Playing audio..." << std::endl;
    } else {
        std::cerr << "Error: Could not play the audio file." << std::endl;
    }

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
};