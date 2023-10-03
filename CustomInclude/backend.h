#pragma once

#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;

cpp_int factorial(long int pokemonSeen, int shinySeen);

float binomialDistribution(long int pokemonSeen, double Odds, int shinySeen, double* ptrResult);

double oddsCalculator(bool oldOdds, bool shinyCharm, double *pointer);
