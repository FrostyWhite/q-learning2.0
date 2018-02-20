#include "ANN.hpp"

/*sigmoid for neural network*/
double sigmoid(double number)
{
	return double(1 / (1 + 1 / pow(2.7, number)));
}

/*returns random values in range of [-1,1]*/
double random_weight()
{
	return (((rand() % 512) - 256) / double(256));
}

/*creates the initial parameters of an artificial neural network*/
ANN::ANN(unsigned int n_inputs, unsigned int n_outputs, unsigned int hidden_layers, unsigned int hidden_layer_size)
	:n_inputs(n_inputs), n_outputs(n_outputs), hidden_layers(hidden_layers), hidden_layer_size(hidden_layer_size) 
{
    srand((unsigned int) time(NULL));
	weight_matrices.push_back(create_random_matrix(n_inputs, hidden_layer_size));

	for (unsigned int n = 1; n < hidden_layers; n++)
	{
		weight_matrices.push_back(create_random_matrix(hidden_layer_size, hidden_layer_size));
	}
	weight_matrices.push_back(create_random_matrix(hidden_layer_size, n_outputs));
}

/*returns random matrix*/
std::vector<std::vector<weight_type>> ANN::create_random_matrix(unsigned int asize, unsigned int bsize)
{
	std::vector<std::vector<weight_type>> ret;
	for (unsigned int i = 0; i < asize; i++)
	{
		std::vector<weight_type> vect;
		for (unsigned int j = 0; j < bsize; j++)
		{
			weight_type r;
			r = { random_weight(),random_weight(),random_weight(),random_weight(), 1, 0 };
			vect.push_back(r);
		}
		std::cout << std::endl;
		ret.push_back(vect);
	}
	std::cout << std::endl;
	return ret;
}

/*saves progress to a file*/
void ANN::save_to_file()
{
	std::ofstream write_file;
	write_file.open("save.txt");

	if (write_file.is_open())
	{
		write_file << n_inputs << " " << n_outputs << " " << hidden_layers << " " << hidden_layer_size << std::endl;
		for (auto m = weight_matrices.begin(); m != weight_matrices.end(); m++)
		{
			write_matrix(write_file, *m);
			write_file << std::endl;
		}
		write_file.close();
	}
    /*else
	{
        throw std::exception( "File can not be opened for writing" );
    }*/
}

/*writes matrix to stream*/
std::ofstream& ANN::write_matrix(std::ofstream& ofs, std::vector<std::vector<weight_type>>& matrix)
{
	for (auto i : matrix)
	{
		for (auto r : i)
		{
			ofs << r.w1 << " " << r.w0 << " " << r.Q1 << " " << r.Q0 << " " << r.d_t << " " << r.nn << " ";
		}
		ofs << std::endl;
	}
	return ofs;
}

/*reads ann parameters from a file*/
ANN::ANN()
{
		std::ifstream r_file;
        r_file.open("save.txt");
		r_file >> n_inputs >> n_outputs >> hidden_layers >> hidden_layer_size;
		read_matrix(r_file, hidden_layer_size, n_inputs);

		for (unsigned int i = 1; i < hidden_layers; i++)
		{
			read_matrix(r_file, hidden_layer_size, hidden_layer_size);
		}
		read_matrix(r_file, n_outputs, hidden_layer_size);
		r_file.close();
}

/*reads matrix from a stream*/
void ANN::read_matrix(std::ifstream& ifs, unsigned int asize, unsigned int bsize) 
{
	std::vector<std::vector<weight_type>> matrix;
	double w1, w0, Q1, Q0;
	unsigned int d_t, nn;

	for (unsigned int i = 0; i < bsize; i++)
	{
		std::vector<weight_type> vector;
		for (unsigned int j = 0; j < asize; j++)
		{
			ifs >> w1 >> w0 >> Q1 >> Q0 >> d_t >>nn;
			weight_type r;
			r = { w1, w0, Q1, Q0 ,d_t,nn};
			vector.push_back(r);
		}
		matrix.push_back(vector);
	}
	weight_matrices.push_back(matrix);
}

/*
* interface for any type of neural network
* at the moment tunes the q values and works with the current weight type
*/
std::vector<double> ANN::ann_raw_operating_interface(std::vector<input_type>& input_params, double Q1 = 1)
{
	std::vector<double> layer_buffer1, layer_buffer2;

	for (auto i : input_params) 
	{
		layer_buffer1.push_back(sigmoid(double(i)));
	}
	for (auto matrix = weight_matrices.begin(); matrix != weight_matrices.end(); matrix++) 
	{
		auto n = 0;
		for (unsigned int i = 0; i < (matrix == weight_matrices.end() - 1 ? n_outputs : hidden_layer_size); i++)
		{
			double sum = 0;
			unsigned int ind = 0;
			for (auto vector = (*matrix).begin(); vector != (*matrix).end(); vector++)
			{
				auto value = (*(vector->begin() + n)).w0;
				auto putvalue = (*layer_buffer1.begin() + ind);
				auto product = value*putvalue;

				//calculate change in q_ave and add +1 to d_t
				(*(vector->begin() + n)).Q1 = ((*(vector->begin() + n)).Q1*(*(vector->begin() + n)).d_t + Q1)/ (((*(vector->begin() + n)).d_t)+1);
				(*(vector->begin() + n)).d_t++;
				sum += product;
				ind++;
			}
			n++;
			double sig = sigmoid(sum);
			layer_buffer2.push_back(sig);
		}
		layer_buffer1 = layer_buffer2;
		layer_buffer2.clear();
	}
	return layer_buffer1;
}

/*q_tune attempts to change the weights by each round selecting
* sqrt(x*y) weights of each matrix and tunes them according to the
* change of average q over time measured since the last tuning
* 
* this should head towards some maximum, not make too hasty changes and also it should not get stuck
*/
void ANN::Q_tune()
{
	double c1 = double(0.5);
	double c2 = double(1.1);

	for (unsigned int i = 0; i <= hidden_layers; i++)
	{
		unsigned int a = (i == 0 ? n_inputs : hidden_layer_size);
		unsigned int b = (i == hidden_layers ? n_outputs : hidden_layer_size);

        for (unsigned int j = 0; j < (unsigned int) sqrt(a*b); j++)
		{
			unsigned int rand_a = rand()%(a);
			unsigned int rand_b = rand() % (b);
			
			auto m = weight_matrices.begin() + i;
			auto v = (*m).begin() + rand_a;
			auto w_struct = *((*v).begin() + rand_b);
			auto d_Q = w_struct.Q1 - w_struct.Q0;
			auto bw0 = w_struct.w0;
			auto bw1 = w_struct.w1;

			if (d_Q < 0) 
			{
				w_struct.w1 = (bw0 + bw1)*c1;
				w_struct.w0 = bw1;
			}
			else 
			{
				if (d_Q > 0) 
				{
					w_struct.w1 = bw1 + (bw1 - bw0)*c2;
					w_struct.w0 = bw1;
				}
			}
			w_struct.Q0 = w_struct.Q1;
			w_struct.d_t = 1;
			w_struct.nn++;
			*((*v).begin() + rand_b) = w_struct;
		}
	}
}

/*
* operating interface for car type ann with 6 outputs
* makes two choises from 6 inputs
*/
std::vector<unsigned int> ANN::car_operating_interface(std::vector<input_type> input_params, double Q1)
{
	std::vector<unsigned int> ret;
	auto dec = this->ann_raw_operating_interface(input_params, Q1);
	std::vector<unsigned int> i = { 0,3 };
	for (auto j : i)
	{
		auto greatest = *(dec.begin() + j);
		unsigned int g_i = 0;
		for (unsigned int x = 1; x < 3; x++)
		{
			if (*(dec.begin() + j + x) > greatest) {
				greatest = *(dec.begin() + j + x);
				g_i = x;
			}
		}
		ret.push_back(g_i);
	}
	return ret;
}
