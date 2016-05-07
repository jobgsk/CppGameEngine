#ifndef MAP_PARSER_H_
#define MAP_PARSER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


#include <cstdlib>
#include <vector>
#include "../GameObject.h"

using namespace std;

void ParseMap(string filename);

bool ParseNode(const char *ch, float px, float pz);
bool ParseFlore(const char *ch, float px, float pz);
bool ParseWall(const char *ch, float px, float pz);
bool ParseBox(const char *ch, float px, float pz);
bool ParsePlayer(const char *ch, float px, float pz);
bool ParseEnemy(const char *ch, float px, float pz);
bool ParseGirl(const char *ch, float px, float pz);

#endif /* MAP_PARSER_H_ */