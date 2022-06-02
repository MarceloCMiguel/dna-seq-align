#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
struct SubstringIndex
{
    int start;
    int size;
};

struct CombinationIndex
{
    int start_a;
    int start_b;
    int size;
};

std::vector<SubstringIndex> generate_substrings_index(int len_word, int max_size)
{
    std::vector<SubstringIndex> substrings_index;
    for (int i = 0; i < len_word; i++)
    {
        for (int size = 1; size < max_size; size++)
        {
            if (i + size < len_word)
            {
                SubstringIndex sub;
                sub.start = i;
                sub.size = size;
                substrings_index.push_back(sub);
            }
        }
    }
    return substrings_index;
}

std::vector<CombinationIndex> generate_all_combinations(int len_word_a, int len_word_b, int max_size)
{
    std::vector<CombinationIndex> combination_vector;
    for (int size = 1; size <= max_size; size++)
    {
        for (int start_a = 0; start_a < len_word_a; start_a++)
        {
            if (start_a + size <= max_size)
            {
                for (int start_b = 0; start_b < len_word_b; start_b++)
                {
                    if (start_b + size <= max_size)
                    {
                        CombinationIndex comb_index;
                        comb_index.start_a = start_a;
                        comb_index.start_b = start_b;
                        comb_index.size = size;
                        combination_vector.push_back(comb_index);
                    }
                }
            }
        }
    }
    return combination_vector;
}

struct calculate_score_gpu
{
    // INSIRA AQUI O ENGINE A DISTRIBUTION
    //   prg(florat _a = 0.f, float _b=1.f) : a(_a), b(_b) {}
    __device__ __host__ double operator()(const char &a, const char &b)
    {
        if (a == b)
        {
            return 2;
        }
        else if ((a == '-') || (b == '-'))
        {
            return -1;
        }
        else
        {
            return -1;
        }
    }
};

int main()
{
    int n;
    int m;
    std::cin >> n >> m;
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::vector<char> a;
    std::vector<char> b;

    std::cout << "Seq1: ";
    for (int i = 1; i <= n; i++)
    {
        char temp;
        std::cin >> temp;
        a.push_back(temp);
        std::cout << temp;
    }
    std::cout << std::endl;

    std::cout << "Seq2: ";
    for (int j = 1; j <= m; j++)
    {
        char temp;
        std::cin >> temp;
        b.push_back(temp);
        std::cout << temp;
    }

    // swap para que o a sempre seje a maior sequência
    if (m > n)
    {
        a.swap(b);
        std::swap(n, m);
    }

    std::cout << std::endl;
    std::vector<SubstringIndex> sub_a_index = generate_substrings_index(a.size(), b.size());
    std::vector<SubstringIndex> sub_b_index = generate_substrings_index(b.size(), b.size());
    std::vector<CombinationIndex> list_combinations = generate_all_combinations(a.size(), b.size(), b.size());
    // for(int i = 0; i < list_combinations.size();i++){
    //     std::cout<<list_combinations[i].start_a<<" "<< list_combinations[i].start_b<< " "<< list_combinations[i].size << std::endl;
    // }
    thrust::device_vector<char> a_gpu(a);
    thrust::device_vector<char> b_gpu(b);
    thrust::device_vector<char> result(b);
    std::vector<int> scores;
    scores.resize(list_combinations.size());
    for (int i = 0; i < list_combinations.size(); i++)
    {
        CombinationIndex comb_index = list_combinations[i];
        int start_a = comb_index.start_a;
        int start_b = comb_index.start_a;
        int end_b = comb_index.start_a + comb_index.size;

        // std::cout<<comb_index.start_a<< " "<< comb_index.start_b << " "<<comb_index.size<< std::endl;
        thrust::transform(b_gpu.begin() + start_b, b_gpu.begin() + end_b,
                          a_gpu.begin() + start_a, result.begin(),
                          calculate_score_gpu());
        int sum = thrust::reduce(result.begin(), result.begin() + comb_index.size, (int)0, thrust::plus<int>());
        // std::cout<<sum<<std::endl;
        scores[i] = sum;
    }
    int score_max = -1 * b.size();
    for (int i = 0; i < scores.size(); i++)
    {
        // std::cout<<scores[i]<< " ";
        if (score_max < scores[i])
        {
            score_max = scores[i];
        }
    }
    std::cout << score_max;

    // // int sum1 = thrust::transform_reduce(a_gpu.begin(),a_gpu.end(),b_gpu.begin(),calculate_score_gpu(),0,thrust::maximum<int>());
    // int sum = thrust::reduce(result.begin(), result.end(), (int) 0, thrust::plus<int>());
    // std::cout<<sum<<std::endl;
}
