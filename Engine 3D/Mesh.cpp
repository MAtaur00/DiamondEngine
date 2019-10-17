#include "Primitive.h"
#include "Glew/include/glew.h"
#include "Application.h"
#include "ComponentTexture.h"

void Mesh::InnerRender() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertex.id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index.id);

	if (parent)
	{
		LOG("tengo papá");
		ComponentTexture* tex = (ComponentTexture*)parent->GetComponent(CompTexture);
		if (tex)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex->GetID());
			LOG("tengo textura");
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, uvs.id);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, index.size, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	
}