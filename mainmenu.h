#ifndef MAINMENU_H
#define MAINMENU_H

#include "network.h"

int readInt(const string &prompt);

int flowTopology(Network &net);
int flowQuery(Network &net);
int mainMenu(Network &net);

#endif // MAINMENU_H
