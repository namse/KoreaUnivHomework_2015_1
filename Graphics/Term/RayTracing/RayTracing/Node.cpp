#include "stdafx.h"
#include "Node.h"


void Namse::Node::MoveBy(Vector& vector)
{
	m_Position += vector;
}

void Namse::Node::MoveTo(Vector& vector)
{
	m_Position += vector;
}

void Namse::Node::AddChild(Node* node)
{
	m_Childs.push_back(node);
}

void Namse::Node::RemoveChild(Node* node)
{
	auto it = std::find(m_Childs.begin(), m_Childs.end(), node);
	if (it != m_Childs.end())
		m_Childs.erase(it);
}

void Namse::Node::OnDraw(Vector& BasePosition)
{
	Vector NextBasePosition = BasePosition + m_Position;
	for (auto& child : m_Childs)
		child->OnDraw(NextBasePosition);
}
