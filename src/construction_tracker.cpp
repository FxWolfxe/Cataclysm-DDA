#include "construction_tracker.h"

#include "event.h"

void construction_tracker::notify(const cata::event& event)
{
    if(event.type() == event_type::player_completes_construction)
    {
        const construction_str_id constructed = construction_str_id(event.get<std::string>("construction_id"));
        constructed_tracker[constructed] += 1;
    }

}

int construction_tracker::get_player_constructed_count(const construction_str_id& id) const
{
    const auto& itr = constructed_tracker.find(id);
    if (itr == constructed_tracker.end()) return 0; 
    return itr->second;
}

int construction_tracker::get_player_total_constructed_count() const
{
    int counter = 0;
    for(const auto& pair: constructed_tracker)
    {
        counter += pair.second;
    }
    return counter; 

}

void construction_tracker::clear()
{
    constructed_tracker.clear();
}

