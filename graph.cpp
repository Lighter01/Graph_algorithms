#include "graph.h"

#include <climits>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "function_params.h"

graph::graph() : full_sum(0)
{

}

graph::graph(const int& nodes_n, const int& l_bound, const int& r_bound) : full_sum(0)
{
    for (int i = 0; i < nodes_n; ++i) {
        this->matrix.emplace_back();
        for (int j = 0; j < nodes_n; ++j) {
            if (i != j) {
                this->matrix.at(i).emplace_back(std::uniform_int_distribution<int>(l_bound, r_bound)(fn::gen));
            }
            else {
                this->matrix.at(i).emplace_back(0); // which number to choose as a marker of no way? LONG_MAX? INT_MAX?
            }
        }
    }
}

void graph::read_graph(const std::string &path)
{
    std::ifstream matrix_file(path);
    std::string line;
    std::stringstream line_stream;
    int line_ind = 0;
    while (std::getline(matrix_file, line)) {
        line_stream << line;
        this->matrix.emplace_back();
        while (std::getline(line_stream, line, ',')) {
            this->matrix.at(line_ind).emplace_back(std::stoi(line));
        }
        ++line_ind;
        line_stream.clear();
    }
    matrix_file.close();
}

void graph::complete_graph()
{
    int m_size = this->matrix.size();
    for(int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (this->matrix.at(i).at(j) != 0 && i != j) {
                full_sum += this->matrix.at(i).at(j);
            }
        }
    }
    for(int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (this->matrix.at(i).at(j) == 0 && i != j) {
                this->matrix.at(i).at(j) = full_sum;
            }
        }
    }
}

std::vector<std::vector<int>> graph::get_matrix() const
{
    return this->matrix;
}

std::vector<std::vector<int>>& graph::change_matrix()
{
    return this->matrix;
}

long long graph::get_full_sum()
{
    return this->full_sum;
}

graph::~graph()
{

}

std::ostream& operator<< (std::ostream& out, const graph& gr)
{
    for (int i = 0; i < gr.matrix.size(); ++i) {
        for (int j = 0; j < gr.matrix.at(i).size(); ++j) {
            out << std::setw(3) << gr.matrix.at(i).at(j) << " ";
        }
        out << '\n';
    }
    return out;
}
