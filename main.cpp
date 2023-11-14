#include "Simplex.h"
#include <vector>
#include <iostream>
using namespace std;

struct InputValues {
    int numberOfVariables, numberOfConstraints;
    vector<vector<float>> constraintCoefficients;
    vector<float> constraintValues, targetFunction;
};

InputValues input(){
    InputValues inputValues;
    cout << "Enter number of variables:\n";
    cin >> inputValues.numberOfVariables;
    cout << "Enter number of constraints:\n";
    cin >> inputValues.numberOfConstraints;
    
    cout << "Enter constraints:\n";
    vector<char> signs = vector<char>(inputValues.numberOfConstraints);
    float tmp;
    for (int i=0; i < inputValues.numberOfConstraints; i++){
        inputValues.constraintCoefficients.push_back(vector<float>(inputValues.numberOfVariables));
        for (int j = 0; j < inputValues.numberOfVariables; j++){
            cin >> inputValues.constraintCoefficients[i][j];
        }
        cin >> signs[i];
        cin >> tmp;
        inputValues.constraintValues.push_back(tmp);
    }
    cout << "Enter traget function coefficient:\n";
    for (int i = 0; i < inputValues.numberOfVariables; i++){
        cin >> tmp;
        inputValues.targetFunction.push_back(tmp * (-1));
    }
    int additionalVariablesNumber = 0;
    for (int i = 0; i < inputValues.numberOfConstraints; i++){
        switch (signs[i]){
            case '=':
                break;
            case '<':
                for (int j = 0; j < inputValues.numberOfConstraints; j++){
                    inputValues.constraintCoefficients[j].push_back(0);
                }
                inputValues.constraintCoefficients[i][inputValues.numberOfVariables + additionalVariablesNumber] = 1;
                additionalVariablesNumber++;
                break;
        }
    }
    for (int i = 0; i < additionalVariablesNumber; i++) {
        inputValues.targetFunction.push_back(0);
    }
    return inputValues;
    
}

int main()
{
    
    InputValues inputValues = input();
    
    Simplex simplex(inputValues.constraintCoefficients, inputValues.constraintValues, inputValues.targetFunction);
    simplex.calculateSimplex();


    return 0;
}
