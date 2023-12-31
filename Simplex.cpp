#include <iostream>
#include <cmath>
#include <vector>
#include "Simplex.h"
using namespace std;



Simplex::Simplex(vector <vector<float> > matrix,vector<float> b ,vector<float> c){
    maximum = 0;
    isUnbounded = false;
    rows = matrix.size();
    cols = matrix[0].size();
    A.resize( rows , vector<float>( cols , 0 ) );
    B.resize(b.size());
    C.resize(c.size());




    for(int i= 0;i<rows;i++){             //pass A[][] values to the metrix
        for(int j= 0; j< cols;j++ ){
            A[i][j] = matrix[i][j];

        }
    }



    for(int i=0; i< c.size() ;i++ ){      //pass c[] values to the B vector
        C[i] = c[i] ;
    }
    for(int i=0; i< b.size();i++ ){      //pass b[] values to the B vector
        B[i] = b[i];
    }
}

bool Simplex::simplexAlgorithmCalculataion(){
    //check whether the table is optimal,if optimal no need to process further
    if(checkOptimality()==true){
	    return true;
    }

    //find the column which has the pivot.The least coefficient of the objective function(C array).
    int pivotColumn = findPivotColumn();


    if(isUnbounded == true){
        cout<<"Error unbounded"<<endl;
	    return true;
    }

    //find the row with the pivot value.The least value item's row in the B array
    int pivotRow = findPivotRow(pivotColumn);

    //form the next table according to the pivot value
    doPivotting(pivotRow,pivotColumn);

    return false;
}

bool Simplex::checkOptimality(){
     //if the table has further negative constraints,then it is not optimal
    bool isOptimal = false;
    int positveValueCount = 0;

    //check if the coefficients of the objective function are negative
    for(int i=0; i<C.size();i++){
        float value = C[i];
        if(value >= 0){
            positveValueCount++;
        }
    }
    //if all the constraints are positive now,the table is optimal
    if(positveValueCount == C.size()){
        isOptimal = true;
        print();
    }
    return isOptimal;
}

void Simplex::doPivotting(int pivotRow, int pivotColumn){

    float pivetValue = A[pivotRow][pivotColumn];//gets the pivot value

    float pivotRowVals[cols];//the column with the pivot

    float pivotColVals[rows];//the row with the pivot

    float rowNew[cols];//the row after processing the pivot value

    maximum = maximum - (C[pivotColumn]*(B[pivotRow]/pivetValue));  //set the maximum step by step
     //get the row that has the pivot value
     for(int i=0;i<cols;i++){
        pivotRowVals[i] = A[pivotRow][i];
     }
     //get the column that has the pivot value
     for(int j=0;j<rows;j++){
        pivotColVals[j] = A[j][pivotColumn];
    }

    //set the row values that has the pivot value divided by the pivot value and put into new row
     for(int k=0;k<cols;k++){
        rowNew[k] = pivotRowVals[k]/pivetValue;
     }

    B[pivotRow] = B[pivotRow]/pivetValue;


     //process the other coefficients in the A array by subtracting
     for(int m=0;m<rows;m++){
        //ignore the pivot row as we already calculated that
        if(m !=pivotRow){
            for(int p=0;p<cols;p++){
                float multiplyValue = pivotColVals[m];
                A[m][p] = A[m][p] - (multiplyValue*rowNew[p]);
                //C[p] = C[p] - (multiplyValue*C[pivotRow]);
                //B[i] = B[i] - (multiplyValue*B[pivotRow]);
            }

        }
     }

    //process the values of the B array
    for(int i=0;i<B.size();i++){
        if(i != pivotRow){

                float multiplyValue = pivotColVals[i];
                B[i] = B[i] - (multiplyValue*B[pivotRow]);

        }
    }
        //the least coefficient of the constraints of the objective function
        float multiplyValue = C[pivotColumn];
        //process the C array
         for(int i=0;i<C.size();i++){
            C[i] = C[i] - (multiplyValue*rowNew[i]);

        }


     //replacing the pivot row in the new calculated A array
     for(int i=0;i<cols;i++){
        A[pivotRow][i] = rowNew[i];
     }


}

    //print the current A array
void Simplex::print(){
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<A[i][j] <<" ";
        }
        cout<<""<<endl;
    }
    cout<<""<<endl;
}

    //find the least coefficients of constraints in the objective function's position
int Simplex::findPivotColumn(){

    int location = 0;
    float minm = C[0];



    for(int i=1;i<C.size();i++){
        if(C[i]<minm){
            minm = C[i];
            location = i;
        }
    }

    return location;

}

    //find the row with the pivot value.The least value item's row in the B array
int Simplex::findPivotRow(int pivotColumn){
    float positiveValues[rows];
    vector<float> result(rows,0);
    //float result[rows];
    int negativeValueCount = 0;

    for(int i=0;i<rows;i++){
        if(A[i][pivotColumn]>=0){
            positiveValues[i] = A[i][pivotColumn];
        }
        else{
            positiveValues[i]=0;
            negativeValueCount+=1;
        }
    }
    //checking the unbound condition if all the values are negative ones
    if(negativeValueCount==rows){
        isUnbounded = true;
    }
    else{
        for(int i=0;i<rows;i++){
            float value = positiveValues[i];
            if(value>0){
                result[i] = B[i]/value;

            }
            else{
                result[i] = 0;
            }
        }
    }
    //find the minimum's location of the smallest item of the B array
    float minimum = 99999999;
    int location = 0;
    for(int i=0;i<sizeof(result)/sizeof(result[0]);i++){
        if(result[i]>0){
            if(result[i]<minimum){
                minimum = result[i];

                location = i;
            }
        }

    }

    return location;

}

void Simplex::calculateSimplex(){
    bool end = false;

    cout<<"initial array(Not optimal)"<<endl;
    print();

    cout<<" "<<endl;
    cout<<"final array(Optimal solution)"<<endl;


    while(!end){

        bool result = simplexAlgorithmCalculataion();

        if(result==true){

            end = true;


            }
    }
    cout<<"Answers for the Constraints of variables"<<endl;

    for(int i=0;i< A.size(); i++){  //every basic column has the values, get it form B array
        int count0 = 0;
        int index = 0;
        for(int j=0; j< rows; j++){
            if(A[j][i]==0.0){
                count0 += 1;
            }
            else if(A[j][i]==1){
                index = j;
            }


        }

        if(count0 == rows -1 ){

            cout<<"variable"<<index+1<<": "<<B[index]<<endl;  //every basic column has the values, get it form B array
        }
        else{
            cout<<"variable"<<index+1<<": "<<0<<endl;

        }

    }


   cout<<""<<endl;
   cout<<"maximum value: "<<maximum<<endl;  //print the maximum values
}

