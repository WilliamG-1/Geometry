// #include "model.h"

// Model::Model(char* path)
// {
//     loadModel(path);
// }
// void Model::Draw(Shader &shader)
// {
//     for(unsigned int i = 0; i < meshes.size(); i++)
//         meshes[i].Draw(shader);
// }  

// void Model::loadModel(string path)
// {
//     Assimp::Importer import;
//     const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
//     if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
//     {
//         cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
//         return;
//     }
//     directory = path.substr(0, path.find_last_of('/'));

//     processNode(scene->mRootNode, scene);
// }  

// void Model::processNode(aiNode *node, const aiScene *scene)
// {
//     // process all the node's meshes (if any)
//     for(unsigned int i = 0; i < node->mNumMeshes; i++)
//     {
//         aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
//         meshes.push_back(processMesh(mesh, scene));			
//     }
//     // then do the same for each of its children
//     for(unsigned int i = 0; i < node->mNumChildren; i++)
//     {
//         processNode(node->mChildren[i], scene);
//     }
// }  