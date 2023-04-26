#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <ostream>
#include <fstream>
#include <string>

// NO edge is equal to 0

class graph
{
public:
    graph();
    graph(const int& nodes_n, const int& l_bound, const int& r_bound); // complete graph generator

    void read_graph(const std::string& path);
    void complete_graph(); // Max length of edge is full_sum of matrix

    std::vector<std::vector<int>> get_matrix() const;
//    std::vector<std::vector<int>>& change_matrix();
    long long get_full_sum();

    ~graph();

    friend std::ostream& operator<< (std::ostream&, const graph&);

private:
    std::vector<std::vector<int>> matrix;
    long long full_sum;
};

#endif // GRAPH_H
