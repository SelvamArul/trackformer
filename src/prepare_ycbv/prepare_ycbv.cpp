#include <iostream>
#include <fstream>
#include <tbb/tbb.h>
#include "json.hpp"

using json=nlohmann::json;

#include <tbb/parallel_for.h>

// area bbox bbox_visib category_id id image_id intrinsic iscrowd pose segmentation segmentation_all
int main()
{
    std::ifstream file;
    file.open("/home/user/periyasa/bkp_instances_test.json");
    json j;
    file >> j;
    for (auto& el : j.items()) 
    {
        std::cout << el.key()  << "\n";
    }
    int count = 0; 
    for (auto& el : j["annotations"].items())
    {
        std::cout << el.key()  << "\n";


        /*     std::cout<<al.key()<<" "; */
        /* } */
        std::cout<<el.value()<<"\n";
        std::cout<<el.value()["image_id"]<<" "<<" category_id "<< el.value()["category_id"]<<"";
        std::cout<<"\n";
        count++;
        if(count == 25)
            break;
    }

    auto values = std::vector<double>(10000);

    tbb::parallel_for( tbb::blocked_range<int>(0,values.size()),
                       [&](tbb::blocked_range<int> r)
    {
        for (int i=r.begin(); i<r.end(); ++i)
        {
            values[i] = std::sin(i * 0.001);
        }
    });

    double total = 0;

    for (double value : values)
    {
        total += value;
    }

    std::cout << total << std::endl;

    std::cout<<"Alles Gut!!!"<<std::endl;
    return 0;
}
