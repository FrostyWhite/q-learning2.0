#ifndef __ANN__H_
#define __ANN__H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <time.h>
#include <string>
#include <array>
#include <list>

// ANN creates and operates a neural network.

struct weight_type
{
//w1 current weight | w2 previous weight | Q1 & Q2 q-values|dt time since last weight tune| how many tunes have been performed for the cell
	double w1, w0, Q1, Q0;
	unsigned int d_t, nn;
};

#define input_type double

class ANN {

public:
	ANN (unsigned int n_inputs, unsigned int n_outputs, unsigned int hidden_layers, unsigned int hidden_layer_size);
    ANN ();
    ~ANN() {}
	
	std::vector<double> ann_raw_operating_interface(std::vector<input_type>& input_params, double Q1);
    std::vector<unsigned int> car_operating_interface(std::vector<input_type> input_params, double Q1);
	void save_to_file();
	void Q_tune();
	std::vector<std::vector<weight_type>> create_random_matrix(unsigned int asize, unsigned int bsize);
	void read_matrix(std::ifstream& ifs, unsigned int asize, unsigned int bsize);
	std::ofstream& write_matrix(std::ofstream& ofs, std::vector<std::vector<weight_type>>& matrix);

private:
	unsigned int n_inputs, n_outputs, hidden_layers, hidden_layer_size;
	std::vector<std::vector<std::vector<weight_type>>> weight_matrices;
};

#endif //__ANN__H_
