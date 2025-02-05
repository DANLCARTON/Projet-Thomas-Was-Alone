#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "shape.hpp"
#include "personnages.hpp"
#include "text.hpp"

void drawLevel(const int level, int* nbPersos, int* nbBlocs, Perso listedespersos[], Platform listedesblocs[], Goal listedesgoals[],
            int* currentPerso, bool* firstloop, int framesPerSecond, int* cycle, int* dirCycle,
            Uint32 elapsedTime);

#endif