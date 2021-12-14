#include <iostream>
#include <fstream>
#include <tbb/tbb.h>
#include "json.hpp"
#include <atomic>
#include <unordered_map>
#include <typeinfo>
using json=nlohmann::json;

#include <tbb/parallel_for.h>
#include <tbb/parallel_for_each.h>

typedef std::atomic<uint64_t> atomic_value;
typedef std::map<uint64_t, atomic_value> atomic_map;

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
    atomic_map sequence_length;
    std::atomic_long count(0);
    tbb::parallel_for_each(j["annotations"].begin(), j["annotations"].end(), [&] (auto& el)
            {
                sequence_length[(uint64_t) el["image_id"]] += 1;
                count++;
                std::cout<<(uint64_t) el["image_id"] <<" ... " <<count  <<" \n ";
            });
    std::cout<<"Computing Done"<<std::endl;
    /* std::cout << count << std::endl; */
    for(const auto& seq : sequence_length)
    {
        std::cout<<seq.first <<" "<<seq.second<<"\n";
    }

    std::cout<<"Alles Gut!!!"<<std::endl;
    return 0;
}
