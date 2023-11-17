#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/Mesh.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, OGraphicsEngine* graphicsEngine)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    this->graphicsEngine = graphicsEngine;

	setupMesh();
}

void Mesh::setupMesh()
{
    // create buffers/arrays
    graphicsEngine->generateVertexArrayObject(&VAO);
    graphicsEngine->bindVertexArrayObject(VAO);
    // load data into vertex buffers
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    graphicsEngine->createArrayBuffer(&VBO, vertices.size() * sizeof(Vertex), &vertices[0]);
    graphicsEngine->createElementArrayBuffer(&EBO, indices.size() * sizeof(unsigned int), &indices[0]);
    
    // set the vertex attribute pointers
    // vertex Positions
    graphicsEngine->setVertexAttributeArray(0, 3, sizeof(Vertex), (void*)0);
    // vertex normals
    graphicsEngine->setVertexAttributeArray(1, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    graphicsEngine->setVertexAttributeArray(2, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    graphicsEngine->setVertexAttributeArray(3, 3, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    graphicsEngine->setVertexAttributeArray(4, 3, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    graphicsEngine->setVertexAttributeArrayInt(5, 4, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // weights
    graphicsEngine->setVertexAttributeArray(6, 4, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    graphicsEngine->bindVertexArrayObject(0);
    
}

void Mesh::Draw(int shader_id)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string
        

        graphicsEngine->activate2DTexture(i, textures[i].id);

        // now set the sampler to the correct texture unit
        //this logic will build it as something like "material.texture_diffuse1".
        graphicsEngine->setUniformInt(shader_id, ("material." + name + number).c_str(), i);
    }

    // draw mesh
    graphicsEngine->bindVertexArrayObject(VAO);
    graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList, static_cast<unsigned int>(indices.size()));
    graphicsEngine->bindVertexArrayObject(0);

    // always good practice to set everything back to defaults once configured.
    graphicsEngine->reset2DTexture();
}
