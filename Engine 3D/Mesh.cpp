#include "Primitive.h"
#include "Glew/include/glew.h"

//void Mesh::InnerRender() const
//{
//	glEnableClientState(GL_VERTEX_ARRAY);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vertex.id);
//	glVertexPointer(3, GL_FLOAT, 0, NULL);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index.id);
//
//	glBindTexture(GL_TEXTURE_2D, App->import->id);
//
//	glDrawElements(GL_TRIANGLES, index.size, GL_UNSIGNED_INT, NULL);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	glDisableClientState(GL_VERTEX_ARRAY);
//}