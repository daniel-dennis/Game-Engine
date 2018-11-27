// (c) Daniel Dennis 2018

#include "model_loader.hpp"

namespace dd
{
    model_loader::model_loader()
    {
        model_data.mPointCount = 0;
        model_data.mVertices.clear();
        model_data.mNormals.clear();
        model_data.mTextureCoords.clear();
    }

    model_loader::~model_loader()
    {
        glDeleteBuffers(1, &model_info.vertices_VBO);
        glDeleteBuffers(1, &model_info.normals_VBO);
        glDeleteBuffers(1, &model_info.texture_coord_VBO);
    }

    void model_loader::load_mesh_internal(const char* file_name) 
    {
        const aiScene* scene = aiImportFile(file_name, aiProcess_Triangulate | aiProcess_PreTransformVertices); 
        if (!scene) 
        {
            std::cerr << "ERROR: reading mesh " << file_name << std::endl;
            return;
        }

        for (size_t m_i = 0; m_i < scene->mNumMeshes; m_i++) 
        {
            const aiMesh* mesh = scene->mMeshes[m_i];
            model_data.mPointCount += mesh->mNumVertices;
            for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) 
            {
                if (mesh->HasPositions())
                {
                    const aiVector3D* vp = &(mesh->mVertices[v_i]);
                    model_data.mVertices.push_back(glm::vec3(vp->x, vp->y, vp->z));
                }
                if (mesh->HasNormals())
                {
                    const aiVector3D* vn = &(mesh->mNormals[v_i]);
                    model_data.mNormals.push_back(glm::vec3(vn->x, vn->y, vn->z));
                }
                if (mesh->HasTextureCoords(0))
                {
                    const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
                    model_data.mTextureCoords.push_back(glm::vec2(vt->x, vt->y));
                }
                if (mesh->HasTangentsAndBitangents())
                {
                    /* You can extract tangents and bitangents here              */
                    /* Note that you might need to make Assimp generate this     */
                    /* data for you. Take a look at the flags that aiImportFile  */
                    /* can take.                                                 */
                }
            }
        }
        aiReleaseImport(scene);

        return;
    }

    void model_loader::load_mesh(const char* file_name)
    {
        this->load_mesh_internal(file_name);

        // Vertices
        glGenBuffers(1, &model_info.vertices_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, model_info.vertices_VBO);
        glBufferData(GL_ARRAY_BUFFER, model_data.mPointCount * sizeof(glm::vec3), &model_data.mVertices[0], GL_STATIC_DRAW);
        
        // Normnals
        glGenBuffers(1, &model_info.normals_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, model_info.normals_VBO);
        glBufferData(GL_ARRAY_BUFFER, model_data.mPointCount * sizeof(glm::vec3), &model_data.mNormals[0], GL_STATIC_DRAW);

        // Texture coordinates
		glGenBuffers (1, &model_info.texture_coord_VBO);
		glBindBuffer (GL_ARRAY_BUFFER, model_info.texture_coord_VBO);
		glBufferData (GL_ARRAY_BUFFER, model_data.mPointCount * sizeof(glm::vec2), &model_data.mTextureCoords[0], GL_STATIC_DRAW);

        return;
    }
}