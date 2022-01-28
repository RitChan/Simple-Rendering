#include "core/TriangleMesh.h"

#include "eigen3/Eigen/Eigen"
#include "third_party/ObjLoader.h"

bool load_obj_meshes(const std::string &obj_path,
                     std::list<TriangleMesh *> &out) {
    objl::Loader loader;
    bool load_ok = loader.LoadFile(obj_path);
    if (!load_ok) {
        std::cerr << "Failed to load obj: " << obj_path << std::endl;
        return false;
    }
    for (std::size_t i = 0; i < loader.LoadedMeshes.size(); i++) {
        TriangleMesh *mesh = new TriangleMesh();
        objl::Mesh &objl_mesh = loader.LoadedMeshes[i];
        std::vector<Eigen::Vector3f> vertices(objl_mesh.Vertices.size());
        std::vector<Eigen::Vector3f> normals(objl_mesh.Vertices.size());
        std::vector<Eigen::Vector2f> tex_coords(objl_mesh.Vertices.size());
        for (std::size_t i = 0; i < objl_mesh.Vertices.size(); i++) {
            auto &vert = objl_mesh.Vertices[i];
            vertices[i] = Eigen::Vector3f(vert.Position.X, vert.Position.Y,
                                          vert.Position.Z);
            normals[i] =
                Eigen::Vector3f(vert.Normal.X, vert.Normal.Y, vert.Normal.Z);
            tex_coords[i] = Eigen::Vector2f(vert.TextureCoordinate.X,
                                            vert.TextureCoordinate.Y);
        }
        mesh->vertices = std::move(vertices);
        mesh->normals = std::move(normals);
        mesh->tex_uv = std::move(tex_coords);
        std::vector<Eigen::Vector3i> indices(objl_mesh.Indices.size() / 3);
        for (std::size_t i = 0; i < indices.size(); i++) {
            int j = i * 3;
            indices[i] =
                Eigen::Vector3i(objl_mesh.Indices[j], objl_mesh.Indices[j + 1],
                                objl_mesh.Indices[j + 2]);
        }
        mesh->indices = std::move(indices);
        out.push_back(mesh);
    }
    return true;
}
