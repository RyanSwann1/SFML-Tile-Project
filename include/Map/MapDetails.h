#pragma once
struct MapDetails
{
	MapDetails(const int width = 32, const int height = 32)
		: m_width(width),
		m_height(height)
	{}

	int m_height;
	int m_width;
};