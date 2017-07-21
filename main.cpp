#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include <string>

#include "Rosalila/Rosalila.h"
#include "RosalilaFootsies/Footsies.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    rosalila()->init();
    Footsies *footsies = new Footsies();
    footsies->gameLoop();
    return 0;
}
