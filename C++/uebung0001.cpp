#include <iostream>

int main(int argc, char ** argv, char **env)    {
    while(*env) {
        std::cout << ("%s", *env) << std::endl;
        ++env;
    }
}
