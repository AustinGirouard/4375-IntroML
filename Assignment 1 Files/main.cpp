#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

double vecSum(vector<double> vec);
double vecMean(vector<double> vec);
double vecMedian(vector<double> vec);
double vecRange(vector<double> vec);
double covar(vector<double> rm, vector<double> medv);
double cor(vector<double> rm, vector<double> medv);
void print_stats(vector<double> vec);

int main(int argc, char** argv)
{
   ifstream input;
   string line;
   string rm_in, medv_in;
   const int MAX_LEN = 1000;
   vector<double> rm(MAX_LEN);
   vector<double> medv(MAX_LEN);
   string fileName = "Boston.csv";

   cout << "Opening " + fileName + " file." << endl;

   input.open(fileName);
   if (!input.is_open()) {
      cout << "Could not open file " + fileName + "." << endl;
      return 1;
   }

   // Read in header line from CSV
   cout << "Reading line 1" << endl;
   getline(input, line);

   // Print header
   cout << "Heading: " << line << endl;

   int numDataPoints = 0;
   // Read in all data points from csv file
   while (input.good()) {
      // Read in inputs as string
      getline(input, rm_in, ',');
      getline(input, medv_in, '\n');

      // Convert inputs to float and store in vectors
      rm.at(numDataPoints) = stof(rm_in);
      medv.at(numDataPoints) = stof(medv_in);

      numDataPoints++;
   }

   cout << "Old length: " << rm.size() << endl;

   // Refit vector sizes to match the amount of data
   rm.resize(numDataPoints);
   medv.resize(numDataPoints);

   cout << "New length: " << rm.size() << endl;

   // Close input file
   cout << "Closing " + fileName + " file." << endl;
   input.close();

   cout << "Number of data points: " << numDataPoints << endl;

   // Print rm statistics
   cout << "\nStats fr rm" << endl;
   print_stats(rm);

   // Print medv statistics
   cout << "\nStats for medv" << endl;
   print_stats(medv);

   // Calculate and print covariance for rm and medv
   cout << "\n Covariance = " << covar(rm, medv) << endl;

   // Calculate and print correlation for rm and medv
   cout << "\n Correlation = " << cor(rm, medv) << endl;

   return 0;
}


/***********************************************************
* This function finds the sum of all elements in a vector. *
* Input: vector<double> with values.                       *
* Return: Sum of elements in vector.                       *
***********************************************************/
double vecSum(vector<double> vec) {
   double sum = 0;

   // Adds all elements
   for (int i = 0; i < vec.size(); i++)
      sum += vec.at(i);

   return sum;
}


/************************************************************
* This function finds the mean of all elements in a vector. *
* Input: vector<double> with values.                        *
* Return: mean of elements in vector.                       *
************************************************************/
double vecMean(vector<double> vec) { return (vecSum(vec) / vec.size()); }


/**************************************************************
* This function finds the median of all elements in a vector. *
* Input: vector<double> with values.                          *
* Return: median of elements in vector.                       *
**************************************************************/
double vecMedian(vector<double> vec) {
   // Sort and return middle element
   sort(vec.begin(), vec.end());
   return vec.at(vec.size() / 2);
}



/*************************************************************
* This function finds the range of all elements in a vector. *
* Input: vector<double> with values.                         *
* Return: range of elements in vector.                       *
*************************************************************/
double vecRange(vector<double> vec) {
   // Sort and return last element - first element
   sort(vec.begin(), vec.end());
   return vec.at(vec.size() - 1) - (vec.at(0));
}


/******************************************************************************
* This function finds the covariance of elements from 2 vectors, rm and medv. *
* Input: vector<double> rm, vector<double> medv                               *
* Return: covariance of values from rm and medv vectors.                      *
******************************************************************************/
double covar(vector<double> rm, vector<double> medv) {
   double covar = 0;
   double rmMean = vecMean(rm);
   double medvMean = vecMean(medv);
   double numerator = 0;

   // Sum the residuals of each element multiplied together
   for (int i = 0; i < rm.size(); i++)
      numerator += (rm.at(i) - rmMean) * (medv.at(i) - medvMean);

   // Divide sum by size - 1 to get covariance
   covar = numerator / (rm.size() - 1);
   return covar;
}


/*******************************************************************************
* This function finds the correlation of elements from 2 vectors, rm and medv. *
* Input: vector<double> rm, vector<double> medv                                *
* Return: correlation of values from rm and medv vectors.                      *
*******************************************************************************/
double cor(vector<double> rm, vector<double> medv) {
   return covar(rm, medv) / (sqrt(covar(rm, rm)) * sqrt(covar(medv, medv)));
}


/*********************************************************************
* This function prints the sum, mean, median, and range of a vector. *
* Input: vector<double> with values.                                 *
* Return: None.                                                      *
*********************************************************************/
void print_stats(vector<double> vec) {
   cout << "Sum = " << vecSum(vec) << endl;
   cout << "Mean = " << vecMean(vec) << endl;
   cout << "Median = " << vecMedian(vec) << endl;
   cout << "Range = " << vecRange(vec) << endl;
}