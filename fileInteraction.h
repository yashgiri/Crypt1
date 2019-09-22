/*
 Created by Spencer Bouck on 9/21/2019
*/

#pragma once

#include <vector>
typedef unsigned int dataPacket;

std::vector<dataPacket> getInput(char* inFileString);
void pushOutput(std::vector<dataPacket>& data, char* outFileString);