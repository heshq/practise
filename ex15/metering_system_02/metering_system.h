#ifndef METERING_SYSTEM_H
#define METERING_SYSTEM_H
#include <type_traits>// for std::common_type

namespace metering_system
{
    namespace metering_system_inner
    {
        //struct NoMeteringSystem{};
        
        struct BritishSystem{};
        struct InternationalSystem{};
        //for fundamental type
        struct NoMeteringSystem{};
    }
    
    typedef metering_system_inner::BritishSystem BS;
    typedef metering_system_inner::InternationalSystem IS;
    
    static BS const bs;
    static IS const is;
    
    /** 
     *
     *  T1 can only be BritishSystem or InternationalSystem,
     *  which indicate metering system you use.
     *  calculate or compare with different type will cause compile error
     *  when you need conversion of metering system with multiplication or division,
     *  you must point out which metering system you use, like below
     *  Metering< BS, int> a( 4);
     *  a( MS::bs) * 5;
     *
     */
    template< typename T1, typename T2> class Metering;
}//end of namespace metering_system

#include "metering_system_impl.h"

#endif
