#pragma once

#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;

void binomialDistribution(long int pokemonSeen, double Odds, double &binomialResult);

void oddsCalculator(bool oldOdds, bool shinyCharm, double &result);
