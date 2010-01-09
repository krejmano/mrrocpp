#ifndef ECP_WII_ABSOLUTE_GENERATOR_H
#define ECP_WII_ABSOLUTE_GENERATOR_H

#include <string.h>
#include <math.h>

#include "ecp/common/generator/ecp_generator.h"
#include "application/wii_teach/sensor/ecp_mp_s_wiimote.h"
#include "application/wii_teach/generator/ecp_g_wii.h"

namespace mrrocpp {
namespace ecp {
namespace irp6ot {
namespace generator {

#define NO_OF_DEGREES 7

#if (MAX_NO_OF_DEGREES < NO_OF_DEGREES)
#error MAX_NO_OF_DEGREES exceeded
#endif

class wii_absolute : public irp6ot::generator::wii
{
    public:
	/**
	 * Tworzy generator odtwarzajacy orientacje kontrolera
	 * @param zadanie
	 * @param major_axis wartosc wiekszej polosi
	 * @param minor_axis wartosc mniejszej polosi
	 * @author jedrzej
	 */
        wii_absolute (common::task::task& _ecp_task,ecp_mp::sensor::wiimote* _wiimote);

        /**
         * Generuje pierwszy krok
         * @author jedrzej
         */
        virtual bool first_step();

        void preset_position(void);

        virtual void set_position(void);

    protected:
        lib::Homog_matrix rotation_matrix;
};

}
} // namespace irp6ot
} // namespace ecp
} // namespace mrrocpp

#endif //ECP_WII_ABSOLUTE_GENERATOR_H