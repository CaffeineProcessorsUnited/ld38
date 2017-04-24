//
// Created by niels on 17.04.17.
//

#ifndef CPU_COMMON_H
#define CPU_COMMON_H

namespace CPU {
    enum ScreenLayer {
        BACK = 0,
        A,
        B,
        C,
        D,
        E,
        FRONT
    };

    enum MouseButton {
        LEFT,
        MIDDLE,
        RIGHT
    };

    enum ObjectType {
        BACKGROUND,
        TREE,
        CLOUD,
        UNICORN,
        STAR,
        RAIN
    };

    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
}

#endif //CPU_COMMON_H
