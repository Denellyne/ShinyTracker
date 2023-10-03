#include "backend.h"
#include "imgui.h"
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;

cpp_int factorial(long int pokemonSeen, int shinySeen) {
    cpp_int pokemonSeenFactorial = 1;
    cpp_int shinySeenFactorial = 1;
    cpp_int nMinusk = pokemonSeen - shinySeen;
    cpp_int nMinuskFactorial = 1;
    cpp_int result;
    if (pokemonSeen != 0) {

        for (int i = 0; i < pokemonSeen;i++) {
            pokemonSeenFactorial = pokemonSeenFactorial * (pokemonSeen - i);
        }
        if (shinySeen != 0) {
            for (int i = 0; i < shinySeen;i++) {
                shinySeenFactorial = shinySeenFactorial * (shinySeen - i);
            }
        }
        else {
            shinySeenFactorial = 1;
        }
        if (nMinusk != pokemonSeen) {
            for (int i = 0; i < nMinusk;i++) {
                nMinuskFactorial = nMinuskFactorial * (nMinusk - i);
            }
        }
        else {
            nMinuskFactorial = pokemonSeenFactorial;
        }
        result = ((pokemonSeenFactorial) / (shinySeenFactorial * nMinuskFactorial));
        return result;
    }
    return 1;
}

float binomialDistribution(long int pokemonSeen, double Odds, int shinySeen, double *ptrResult) {

    long double result;
    cpp_int binomialCoefficient;
    binomialCoefficient = factorial(pokemonSeen, shinySeen);

    result = ((pow(Odds, shinySeen) * (pow((1 - Odds), (pokemonSeen - shinySeen)))));

    float convertedCoefficient = binomialCoefficient.convert_to<float>();

    result = (1 - (convertedCoefficient * result)) * 100;

    *ptrResult = result;


    return 1;

}


double oddsCalculator(bool oldOdds, bool shinyCharm, double *ptrResult) {

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

    *ptrResult = odds;

    return *ptrResult;
}
