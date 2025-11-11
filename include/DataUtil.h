#ifndef DATAHORAUTIL_H
#define DATAHORAUTIL_H

#include <string>
#include <ctime>

std::time_t converteDataHora(const std::string& s);
std::string formataDataHora(std::time_t ts);

#endif
