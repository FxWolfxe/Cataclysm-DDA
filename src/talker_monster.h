#pragma once
#ifndef CATA_SRC_TALKER_MONSTER_H
#define CATA_SRC_TALKER_MONSTER_H

#include <functional>
#include <list>
#include <string>
#include <vector>

#include "coordinates.h"
#include "monster.h"
#include "talker.h"
#include "type_id.h"

class faction;
class item;
class mission;
class npc;
class time_duration;
class vehicle;
struct tripoint;

/*
 * Talker wrapper class for monster.
 */
class talker_monster_const: public talker_cloner<talker_monster_const>
{
    public:
        explicit talker_monster_const( const monster *new_me ): me_mon_const( new_me ) {
        }
        ~talker_monster_const() override = default;

        // identity and location
        std::string disp_name() const override;

        int posx() const override;
        int posy() const override;
        int posz() const override;
        tripoint pos() const override;
        tripoint_abs_ms global_pos() const override;
        tripoint_abs_omt global_omt_location() const override;

        int pain_cur() const override;

        // effects and values
        bool has_effect( const efftype_id &effect_id, const bodypart_id &bp ) const override;
        effect get_effect( const efftype_id &effect_id, const bodypart_id &bp ) const override;

        std::string get_value( const std::string &var_name ) const override;

        bool has_flag( const flag_id &f ) const override;

        std::string short_description() const override;
        int get_anger() const override;
        int morale_cur() const override;
        int get_friendly() const override;
        bool will_talk_to_u( const Character &u, bool force ) override;
        std::vector<std::string> get_topics( bool radio_contact ) override;
        int get_cur_hp( const bodypart_id & ) const override;
    protected:
        talker_monster_const() = default;
        const monster *me_mon_const;
};

class talker_monster: public talker_cloner<talker_monster, talker_monster_const>
{
    public:
        explicit talker_monster( monster *new_me );
        ~talker_monster() override = default;

        // underlying element accessor functions
        monster *get_monster() override {
            return me_mon;
        }
        const monster *get_monster() const override {
            return me_mon_const;
        }
        Creature *get_creature() override {
            return me_mon;
        }
        const Creature *get_creature() const override {
            return me_mon_const;
        }

        // effects and values
        void add_effect( const efftype_id &new_effect, const time_duration &dur,
                         const std::string &bp, bool permanent, bool force, int intensity
                       ) override;
        void remove_effect( const efftype_id &old_effect ) override;
        void mod_pain( int amount ) override;

        void set_value( const std::string &var_name, const std::string &value ) override;
        void remove_value( const std::string &var_name ) override;

        void set_anger( int ) override;
        void set_morale( int ) override;
        void set_friendly( int ) override;
        void die() override;
    protected:
        talker_monster() = default;
        monster *me_mon;
};
#endif // CATA_SRC_TALKER_MONSTER_H
