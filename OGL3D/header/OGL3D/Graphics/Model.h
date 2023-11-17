#pragma once
#include <OGL3D/Graphics/Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

class OGraphicsEngine;
class Model
{
public:
    //consturctor. Expects a filepath to a 3D model
    Model(std::string path, OGraphicsEngine* graphicsEngine)
    {
        this->graphicsEngine = graphicsEngine;
        loadModel(path);
    }
    void Draw(int shader_id);

public:
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;

private:
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

    OGraphicsEngine* graphicsEngine;
};