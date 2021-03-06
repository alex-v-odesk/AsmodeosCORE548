/*
 * Copyright (C) 2011-2017 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2017 MaNGOS <https://www.getmangos.eu/>
 * Copyright (C) 2006-2014 ScriptDev2 <https://github.com/scriptdev2/scriptdev2/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "instance_zulgurub.h"

enum Yells
{
    SAY_AGGRO                       = 0,
    EMOTE_ZANZIL_ZOMBIES            = 1, // ID - 96319 Zanzil's Resurrection Elixir
    SAY_ZANZIL_ZOMBIES              = 2, // ID - 96319 Zanzil's Resurrection Elixir
    EMOTE_ZANZIL_GRAVEYARD_GAS      = 3, // ID - 96338 Zanzil's Graveyard Gas
    SAY_ZANZIL_GRAVEYARD_GAS        = 4, // ID - 96338 Zanzil's Graveyard Gas
    EMOTE_ZANZIL_BERSEKER           = 5, // ID - 96316 Zanzil's Resurrection Elixir
    SAY_ZANZIL_BERSEKER             = 6, // ID - 96316 Zanzil's Resurrection Elixir
    SAY_PLAYER_KILL                 = 7,
    SAY_DEATH                       = 8
};

enum Spells
{
};

enum Events
{
};

class boss_zanzil : public CreatureScript
{
    public:
        boss_zanzil() : CreatureScript("boss_zanzil") { }

        struct boss_zanzilAI : public BossAI
        {
            boss_zanzilAI(Creature* creature) : BossAI(creature, DATA_ZANZIL) { }

            void Reset() OVERRIDE
            {
                _Reset();
            }

            void EnterCombat(Unit* /*who*/) OVERRIDE
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
            }

            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                _JustDied();
                Talk(SAY_DEATH);
            }

            void KilledUnit(Unit* victim) OVERRIDE
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_PLAYER_KILL);
            }

            void UpdateAI(uint32 diff) OVERRIDE
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                /*
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        default:
                            break;
                    }
                }
                */

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return GetZulGurubAI<boss_zanzilAI>(creature);
        }
};

void AddSC_boss_zanzil()
{
    new boss_zanzil();
}
