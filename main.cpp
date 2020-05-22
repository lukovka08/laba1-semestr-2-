#include <iostream>
#include <string>
#include "items.h"
#include "ui.h"
#define DEFAULT_FILENAME "stock.txt"
using namespace std;

int main(int argc, char* argv[]) {
    string filename = DEFAULT_FILENAME;
    if(argc > 1)
        filename = argv[1];
    UI ui(filename);
    ui.main_loop();
    return 0;
}
