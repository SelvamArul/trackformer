#include <iostream>
#include <fstream>
#include "json.hpp"
#include <typeinfo>
#include <iomanip>
#include <string>
#include <utility>
#include <set>
#include <iterator>
using json=nlohmann::json;


typedef std::unordered_map<uint64_t, uint64_t> seq_map;
typedef std::map<uint64_t, std::set<uint64_t>> track_map;


int GetIndex(std::set<uint64_t>& S, uint64_t K)
{
    // To store the index of K
    int index = 0;

    // Traverse the Set
    for (auto u : S) {

        if (u == K)
            return index;

        index++;
    }

    // If K is not present
    // in the set
    throw std::runtime_error("This should never happen");
    return -1;
}

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

    for (auto& el : j.items()) 
    {
        std::cout << el.key()  << "\n";
    }
    std::cout<<"*****************************\n";

    std::cout<<"*****************************\n";
    for(auto& el :j["annotations"].items())
    {
        uint64_t img_id = el.value()["image_id"];
        auto seq_id = img_id / 1000000;
        annotation_length[ img_id ] += 1;
        
        track_ids[seq_id].insert((uint64_t) el.value()["category_id"]);
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
        std::cout<<track.first <<" \n ";
        for (const auto& img : track.second)
            std::cout <<img<<" ";
    }

    for (auto& el : j["annotations"].items())
    {
        uint64_t img_id = el.value()["image_id"];
        uint64_t category_id = el.value()["category_id"];
        uint64_t seq_id = img_id / 1000000;
        el.value()["seq_length"] = sequence_length[seq_id];
        el.value()["first_frame_image_id"]= seq_id * 1000000;
        int track_id = GetIndex(track_ids[seq_id], category_id);
        el.value()["track_id"] = track_id;
    }
    
    std::ofstream out("out.json");
    out << j <<std::endl;
    std::cout<<"Alles Gut!!!"<<std::endl;
    return 0;
}
