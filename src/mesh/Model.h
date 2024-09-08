#ifndef UNTITLED_MODEL_H
#define UNTITLED_MODEL_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <mesh/Mesh.h>
#include <shader/Shader.h>


class Model
{
public:
    Model(std::string path);
    ~Model();

    void draw(Shader &shader);

private:
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int loadTextureFromFile(const char *path, const std::string &directory);

    std::vector<Mesh> mMeshs;
    std::vector<Texture> mTexturesLoaded;
    std::string mDirectory;
};


#endif // UNTITLED_MODEL_H
