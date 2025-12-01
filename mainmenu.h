#ifndef MAINMENU_H
#define MAINMENU_H

#include "network.h"
#include <string>

int readInt(const std::string &prompt);

int flowTopology(Network &net);
int flowQuery(Network &net);

#endif // MAINMENU_H
