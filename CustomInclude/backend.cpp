#include "backend.h"
#include "imgui.h"
#include <cmath>

void binomialDistribution(long int pokemonSeen, double Odds, double &binomialResult) {

    long double result;

    result = ((1 * (pow((1 - Odds), (pokemonSeen)))));

    result = (1 - (1 * result)) * 100;

    binomialResult = result;

}

void oddsCalculator(bool oldOdds, bool shinyCharm, double &result) {

    double odds;

    if (oldOdds) {
        odds = 0.00012207031;
        if (shinyCharm) {
            odds = odds * 3;
        }
    }
    if (!oldOdds) {

        odds = 0.00024414062;
        if (shinyCharm) {
            odds = odds * 3;
        }
    }

    result = odds;
}
