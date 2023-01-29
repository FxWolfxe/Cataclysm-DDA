#pragma once
#ifndef CATA_SRC_CONSTRUCTION_TRACKER_H
#define CATA_SRC_CONSTRUCTION_TRACKER_H
#include <map>


#include "event_subscriber.h"
#include "itype.h"

class JsonObject;
class JsonOut;


class construction_tracker : public event_subscriber
{
public:
    construction_tracker() = default; 

    void notify(const cata::event&) override;

    /**
     * \brief get the number of the specified constructions completed by the player 
     * \param id the id of the construction to look for 
     * \return the number of constructions completed 
     */
    int get_player_constructed_count(const construction_str_id& id) const;

    /**
     * \brief count the total number of constructed items done by the player 
     * \return the count of total number of constructions done by the player 
     */
    int get_player_total_constructed_count() const; 


    /**
     * \brief clear this tracker 
     */
    void clear();
    void serialize(JsonOut&) const;
    void deserialize(const JsonObject& data);
private: 
    std::unordered_map<construction_str_id, int> constructed_tracker; 
    
};

#endif
