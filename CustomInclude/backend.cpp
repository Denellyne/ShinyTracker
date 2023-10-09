#include "backend.h"
#include "imgui.h"
#include <cmath>
#include <iostream>
#include <future>

void binomialDistribution(long int pokemonSeen, double Odds, double &binomialResult) {

    long double result;
    result = ((1 * (pow((1 - Odds), (pokemonSeen)))));
    result = (1 - (1 * result)) * 100;
    binomialResult = result;
}
double oddsCalculator(bool oldOdds, bool shinyCharm, double &result) {

    double odds;   
    switch (oldOdds) {
    case true:
        odds = 0.00012207031;
        if (shinyCharm) {
            odds = odds * 3;
        }
        result = odds;
        return result;
        break;
    case false:
        odds = 0.00024414062;
        if (shinyCharm) {
            odds = odds * 3;
        }
        result = odds;
        return result;
        break;
    }
    
}
