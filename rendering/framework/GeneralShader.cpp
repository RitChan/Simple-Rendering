#include "framework/GeneralShader.h"
#include "primitive_impl/NullPrimitive.h"

void reset_default(IShader *shader) {}

IPrimitive &vertex_shader_default(IShader *shader) {
    static NullPrimitive primitive;
    return primitive;
}
