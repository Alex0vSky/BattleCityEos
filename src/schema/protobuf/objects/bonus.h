#pragma once // src\schema\protobuf\objects\bonus.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class dealing with displaying the bonus.
 */
class Bonus : public Object {
	using PbBonus_t = A0S_proto::PbBonus;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbBonus_t, T, SETTER, GETTER >;
	pb_data_t< PbBonus_t > m_dataOffline{ new PbBonus_t };
	PbBonus_t *m_fieldsDataPointer = m_dataOffline.get( );

    /**
     * Time since bonus creation.
     */
	Xetter_t< Uint32, &PbBonus_t::set_bonus_show_time, &PbBonus_t::bonus_show_time > m_bonus_show_time{ m_fieldsDataPointer };
    /**
     * Variable storing information about whether the bonus is currently displayed; used for flashing.
     */
	Xetter_t< bool, &PbBonus_t::set_show, &PbBonus_t::show > m_show{ m_fieldsDataPointer };

public:
    /**
     *Creating a bonus.
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - bonus type
     */
    Bonus(double x, double y, sprite_t type);

    /**
     * Bonus drawing function.
     */
    void draw();
    /**
     * Feature updating bonus animations. Permission to delete after a reasonable period of time.
     * Increased flashing frequency if the bonus is about to be removed.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
};
