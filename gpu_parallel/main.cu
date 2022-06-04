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


std::vector<CombinationIndex> generate_all_combinations(int len_word_a, int len_word_b, int max_size)
{
    std::vector<CombinationIndex> combination_vector;
    for (int size = 1; size <= max_size; size++)
    {
        for (int start_a = 0; start_a <= len_word_a-size; start_a++)
        {

                for (int start_b = 0; start_b <= len_word_b-size; start_b++)
                {
                    
                        CombinationIndex comb_index;
                        comb_index.start_a = start_a;
                        comb_index.start_b = start_b;
                        comb_index.size = size;
                        
                        combination_vector.push_back(comb_index);
                        
                    
                
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
    // std::vector<SubstringIndex> sub_a_index = generate_substrings_index(a.size(), b.size());
    // std::vector<SubstringIndex> sub_b_index = generate_substrings_index(b.size(), b.size());
    std::vector<CombinationIndex> list_combinations = generate_all_combinations(a.size(), b.size(), b.size());
    
    
    
    
    thrust::host_vector<char> a_cpu(a);
    thrust::host_vector<char> b_cpu(b);
    thrust::device_vector<char> a_gpu(a_cpu);
    thrust::device_vector<char> b_gpu(b_cpu);
    thrust::device_vector<char> result(b_cpu);
    std::vector<int> scores;
    scores.resize(list_combinations.size());
    // #pragma omp parallel for
    for (int i = 0; i < list_combinations.size(); i++)
    {
        CombinationIndex comb_index = list_combinations[i];
        int start_a = comb_index.start_a;
        int start_b = comb_index.start_b;
        int end_b = comb_index.start_b + comb_index.size;
        
        // std::cout<<comb_index.start_a<< " "<< comb_index.start_b << " "<<comb_index.size<< std::endl;
        thrust::transform(b_gpu.begin() + start_b, b_gpu.begin() + end_b,
                          a_gpu.begin() + start_a, result.begin()+start_b,
                          calculate_score_gpu());
            
        int sum = thrust::reduce(result.begin()+start_b, result.begin() + start_b+comb_index.size, (int)0, thrust::plus<int>());
        scores[i] = sum;
        // std::cout<<sum<<std::endl;
        
    }

    int start_a;
    int start_b;
    int size;
    int score_max = -1 * b.size();
    for (int i = 0; i < scores.size(); i++)
    {
        // std::cout<<scores[i]<< " ";
        if (score_max < scores[i])
        {
            start_a = list_combinations[i].start_a;
            start_b = list_combinations[i].start_b;
            size = list_combinations[i].size;
            score_max = scores[i];
        }
    }
    std::vector<char>sub_a;


    sub_a = std::vector<char>(a.begin() + start_a, a.begin()+start_a+size);
    std::vector<char>sub_b = std::vector<char>(b.begin() + start_b, b.begin()+start_b+size);

    std::cout<<"Sub A: ";
    for(int i = 0; i < sub_a.size(); i++){
        std::cout<<sub_a[i];
    }
    std::cout<<std::endl;
    std::cout<<"Sub B: ";
    for(int i = 0; i < sub_b.size(); i++){
        std::cout<<sub_b[i];
    }
    std::cout<<std::endl;
    std::cout << score_max<<std::endl;


    // int sum1 = thrust::transform_reduce(a_gpu.begin(),a_gpu.end(),b_gpu.begin(),calculate_score_gpu(),0,thrust::maximum<int>());
    // int sum = thrust::reduce(result.begin(), result.end(), (int) 0, thrust::plus<int>());
    // std::cout<<sum<<std::endl;
}
