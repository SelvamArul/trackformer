#include <iostream>
#include <fstream>
#include "json.hpp"
#include <typeinfo>
#include <string>
#include <utility>
using json=nlohmann::json;


typedef std::unordered_map<uint64_t, uint64_t> seq_map;
typedef std::map<std::pair<uint64_t, uint64_t>, uint64_t> track_map;
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
    seq_map sequence_length;
    seq_map annotation_length;
    track_map track_ids;
    int count(0);
    for(auto& el :j["annotations"].items())
    {
        annotation_length[ (uint64_t) el.value()["image_id"] ] += 1;
        track_ids[std::make_pair((uint64_t) el.value()["image_id"] / 1000000, (uint64_t) el.value()["category_id"])] += 1;
        count++;
    }
    std::cout << count << std::endl;
    count = 0;
    for(const auto& seq : annotation_length)
    {
        /* if (seq.second !=6) */
            /* std::cout<<seq.first <<" "<<seq.second<<"\n"; */
            sequence_length[seq.first / 1000000] += 1;
            count++;
    }
    std::cout<<"count "<<count<<std::endl;
    std::cout<<" -------- "<<std::endl;
    
    for(const auto& seq : sequence_length)
    {
        std::cout<<seq.first<<" "<<seq.second<<"\n";
    }
    std::cout<<" ------------- "<<std::endl;
    for(const auto& track : track_ids)
    {
        std::cout<<track.first.first <<" "<<track.first.second<<" "<<track.second<<"\n";
    }

    std::cout<<"Alles Gut!!!"<<std::endl;
    return 0;
}
