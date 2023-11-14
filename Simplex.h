#include <vector>

class Simplex{
    private:
        int rows, cols;
        std::vector<std::vector<float>> A;
        std::vector<float> B;
        std::vector<float> C;
        float maximum;
        bool isUnbounded;
    public:
        Simplex(std::vector<std::vector<float>> matrix, std::vector<float> b ,std::vector<float> c);
        bool simplexAlgorithmCalculataion();
        bool checkOptimality();
        void doPivotting(int pivotRow, int pivotColumn);
        void print();
        int findPivotColumn();
        int findPivotRow(int pivotColumn);
        void calculateSimplex();
};
