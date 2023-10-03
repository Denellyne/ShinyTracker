#include <bitset>
#include <fstream>
#include <iostream>
#include "save&load.h"

namespace SaveLoad{


    void saveData(bool oldOdds, bool shinyCharm,int pokemonSeen,int shinySeen,double* ptrOdds,double* ptrBinomialDistribution) {

        std::ofstream saveData;
        saveData.open("data.txt",std::ofstream::app);
        std::string tempBinary;

        if (saveData) {

            tempBinary = std::bitset<1>(oldOdds).to_string();
            saveData << tempBinary << '\n';
            tempBinary = std::bitset<1>(shinyCharm).to_string();
            saveData << tempBinary << '\n';
            tempBinary = std::bitset<32>(pokemonSeen).to_string();
            saveData << tempBinary << '\n';
            tempBinary = std::bitset<32>(shinySeen).to_string();
            saveData << tempBinary << '\n';
            tempBinary = std::bitset<32>(*ptrOdds).to_string();
            saveData << tempBinary << '\n';
            tempBinary = std::bitset<32>(*ptrBinomialDistribution).to_string();
            saveData << tempBinary << '\n';
      
        }
        else {
        }
    }
    void loadData() {

        std::ifstream loadData;
        loadData.open("data.txt");

        if (loadData) {





        }



    }

}
