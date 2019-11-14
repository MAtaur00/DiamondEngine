#include "ComponentTransform.h"
#include "GameObject.h"


ComponentTransform::ComponentTransform(GameObject* parent) : Component(parent, CompTransform)
{
	
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Inspector()
{
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Position", &position[0], 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			UpdateBoundingBox();
		}
		float3 degRotation = rotation.ToEulerXYZ();
		degRotation = RadToDeg(degRotation);
		if (ImGui::DragFloat3("Rotation", &degRotation[0], 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			SetRotation(DegToRad(degRotation));
			UpdateBoundingBox();
		}
		if (ImGui::DragFloat3("Scale", &scale[0], 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			UpdateBoundingBox();
		}
		if (ImGui::Button("Reset"))
		{
			position = float3::zero;
			rotation = Quat::identity;
			scale = float3::one;
			UpdateBoundingBox();
		}

		ImGui::Separator();

		ImGui::Checkbox("Static", &gameObject->isStatic);
	}
}

void ComponentTransform::SetPos(float x, float y, float z)
{
	SetPos(float3(x, y, z));
}

void ComponentTransform::SetPos(float3 position)
{
	this->position = position;
	UpdateBoundingBox();
}

void ComponentTransform::Move(float3 distance)
{
	this->position = this->position.Add(distance);
	UpdateBoundingBox();
}

float3 ComponentTransform::GetPos() const
{
	return position;
}

float3 ComponentTransform::GetGlobalPos() const
{
	float3 pos;
	GetMatrix().Decompose(pos, Quat(), float3());

	return pos;
}

void ComponentTransform::SetScale(float x, float y, float z)
{
	scale = float3(x, y, z);
	UpdateBoundingBox();
}

void ComponentTransform::SetScale(float3 scale)
{
	this->scale = scale;
	UpdateBoundingBox();
}

void ComponentTransform::Scale(float3 scale)
{
	this->scale = this->scale.Mul(scale);
	UpdateBoundingBox();
}

float3 ComponentTransform::GetScale()
{
	return scale;
}

float3 ComponentTransform::GetGlobalScale()
{
	if (gameObject->parent)
	{
		return scale.Mul(gameObject->parent->transform->GetGlobalScale());
	}
	return scale;
}

void ComponentTransform::SetRotation(Quat rotation)
{
	this->rotation = rotation;
	UpdateBoundingBox();
}

void ComponentTransform::SetRotation(float3 rotation)
{
	this->rotation = Quat::FromEulerXYZ(rotation.x, rotation.y, rotation.z);
	UpdateBoundingBox();
}

void ComponentTransform::Rotate(Quat rotation)
{
	this->rotation = rotation.Mul(this->rotation).Normalized();
	UpdateBoundingBox();
}

Quat ComponentTransform::GetRotation() const
{
	return rotation;
}

Quat ComponentTransform::GetGlobalRotation() const
{
	if (gameObject->parent)
	{
		return rotation.Mul(gameObject->parent->transform->GetGlobalRotation());
	}
	return rotation;
}

void ComponentTransform::SetTransform(float4x4 trans)
{
	trans.Decompose(position, rotation, scale);
	UpdateBoundingBox();
}

void ComponentTransform::SetIdentity()
{
	position = float3::zero;
	rotation = Quat::identity;
	scale = float3::one;
	UpdateBoundingBox();
}

float4x4 ComponentTransform::GetMatrixOGL() const
{
	return GetMatrix().Transposed();
}

float4x4 ComponentTransform::GetMatrix() const
{
	float4x4 localMatrix = GetLocalMatrix();
	if (gameObject->parent)
	{
		return gameObject->parent->transform->GetMatrix().Mul(localMatrix);
	}
	return localMatrix;
}

float4x4 ComponentTransform::GetLocalMatrix() const
{
	return float4x4::FromTRS(position, rotation, scale);
}

void ComponentTransform::UpdateBoundingBox()
{
	OBB obb;
	obb = gameObject->originalBoundingBox.ToOBB();
	obb.Transform(GetMatrix());

	gameObject->boundingBox = obb.MinimalEnclosingAABB();

	for (std::list<GameObject*>::iterator it = gameObject->childs.begin(); it != gameObject->childs.end(); ++it)
	{
		(*it)->transform->UpdateBoundingBox();
	}
}

void ComponentTransform::Save(JSON_Object * parent)
{
	json_object_set_number(parent, "Type", type);
	json_object_set_number(parent, "UUID", uuid);

	// Position
	//------------------------------------------------------------------------
	JSON_Value* pos = json_value_init_object();
	JSON_Object* positionObj = json_value_get_object(pos);

	json_object_set_value(parent, "Position", pos);

	json_object_set_number(positionObj, "X", position.x);
	json_object_set_number(positionObj, "Y", position.y);
	json_object_set_number(positionObj, "Z", position.z);
	//------------------------------------------------------------------------

	// Scale
	//------------------------------------------------------------------------
	JSON_Value* scal = json_value_init_object();
	JSON_Object* scaleObj = json_value_get_object(scal);

	json_object_set_value(parent, "Position", scal);

	json_object_set_number(scaleObj, "X", scale.x);
	json_object_set_number(scaleObj, "Y", scale.y);
	json_object_set_number(scaleObj, "Z", scale.z);
	//------------------------------------------------------------------------

	// Rotation
	//------------------------------------------------------------------------
	JSON_Value* rot = json_value_init_object();
	JSON_Object* rotationObj = json_value_get_object(rot);

	json_object_set_value(parent, "Position", rot);

	json_object_set_number(rotationObj, "X", rotation.x);
	json_object_set_number(rotationObj, "Y", rotation.y);
	json_object_set_number(rotationObj, "Z", rotation.z);
	//------------------------------------------------------------------------
}