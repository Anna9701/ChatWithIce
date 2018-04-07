#ifndef MENU_H
    #define MENU_H

    #include <iostream>
    #include <cstdlib>

    using namespace std;

    class Menu {
        public:
            void printMenu();
            int getChoice();
        private:
            int choice;

            void getInput();
    };

#endif