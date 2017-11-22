#pragma once

struct ColouredVertex {
        float x, y, z;
        float r, g, b;

        ColouredVertex(float mx, float my, float mz) : x(mx), y(my), z(mz) {}
        ColouredVertex(float mx, float my, float mz, float mr, float mg, float mb) : x(mx), y(my), z(mz), r(mr), g(mg), b(mb) {}
};